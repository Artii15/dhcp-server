#include "../inc/server.h"
#include "../inc/dhcp_message.h"
#include "../inc/protocol.h"
#include "../inc/client.h"
#include "../inc/discover_handler.h"
#include "../inc/request_handler.h"
#include "../inc/decline_handler.h"
#include "../inc/release_handler.h"
#include "../inc/inform_handler.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdexcept>

#define MAX_FILTER_SIZE 64

using namespace std;

Server::Server(Config &configuration, AddressesAllocator& allocator, TransactionsStorage& storage)
 	  : config(configuration), addressesAllocator(allocator), transactionsStorage(storage) {

	networkResolver = new NetworkResolver(config);
	const char* interfaceName = config.getInterface();

	serverIp = determineDeviceIp(interfaceName);

	pcapHandle = pcap_create(interfaceName, pcapErrbuf);
	if(pcapHandle == NULL) {
		throw runtime_error(pcapErrbuf);
	}
	pcap_set_snaplen(pcapHandle, 65535);
	if(pcap_activate(pcapHandle) != 0) {
		throw runtime_error(pcapErrbuf);
	}

	lnetHandle = libnet_init(LIBNET_LINK, interfaceName, lnetErrbuf);
	sender = new Sender(lnetHandle);

	setPacketsFilter();
}

uint32_t Server::determineDeviceIp(const char* interfaceName) {
	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	struct ifreq ifr;
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, interfaceName, IFNAMSIZ-1);
	ioctl(fd, SIOCGIFADDR, &ifr);
	close(fd);

	return ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr;
}

void Server::setPacketsFilter() {
	struct bpf_program fp;

	uint16_t bootpServerPort = Protocol::getServicePortByName("bootps", "udp");
	uint16_t bootpClientPort = Protocol::getServicePortByName("bootpc", "udp");

	char filter[MAX_FILTER_SIZE] = {0};
	snprintf(filter, MAX_FILTER_SIZE - 1, "ether proto 0x%04x and udp dst port %u and udp src port %u", ETH_P_IP, bootpServerPort, bootpClientPort);
	if(pcap_compile(pcapHandle, &fp, filter, 0, config.getNetworkMask()) != 0) {
		throw pcapErrbuf;
	}
	if(pcap_setfilter(pcapHandle, &fp) < 0) {
		throw pcapErrbuf;
	}
}

Server::~Server() {
	pcap_close(pcapHandle); 
	libnet_destroy(lnetHandle);
	delete networkResolver;
	delete sender;
}

void Server::listen() {
	pcap_loop(pcapHandle, 0, &Server::dispatch, (u_char*)this);
}

void Server::dispatch(u_char *srv, const struct pcap_pkthdr *header, const u_char *rawMessage) {
	unsigned int dhcpMsgStartPos = sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr);
	struct DHCPMessage* dhcpMsg = (struct DHCPMessage*)(rawMessage + dhcpMsgStartPos);
	Options options(dhcpMsg->options, header->caplen - dhcpMsgStartPos);

	Client client;
	memset(&client, 0, sizeof(client));

	client.hardwareAddress.addressType = dhcpMsg->htype;
	memcpy(client.hardwareAddress.hardwareAddress, dhcpMsg->chaddr, MAX_HADDR_SIZE);

	if(options.exists(CLIENT_IDENTIFIER)) {
		Option& clientIdOption = options.get(CLIENT_IDENTIFIER);
		client.specialId.type = *clientIdOption.value;
		memcpy(client.specialId.value, clientIdOption.value + 1, (CLIENT_SPECIAL_ID_MAX_LEN < clientIdOption.length) ? CLIENT_SPECIAL_ID_MAX_LEN : clientIdOption.length);

		client.identificationMethod = BASED_ON_SPECIAL_ID;
	}
	else {
		client.identificationMethod = BASED_ON_HARDWARE;
	}

	Server& server = *((Server*)srv);
	client.networkAddress = server.networkResolver->determineNetworkAddress(dhcpMsg->giaddr);

	struct iphdr* ipHeader = (struct iphdr*)(rawMessage + sizeof(struct ethhdr));
	uint32_t dstAddr = ntohl(ipHeader->daddr);

	uint8_t operationType = *options.get(DHCP_MESSAGE_TYPE).value;
	switch(operationType) {
		case(DHCPDISCOVER): {
			DiscoverHandler(server.transactionsStorage, client, server.addressesAllocator, server).handle(*dhcpMsg, options, dstAddr);
			break;	
		}
		case(DHCPREQUEST): {
			RequestHandler(server.transactionsStorage, client, server.addressesAllocator, server).handle(*dhcpMsg, options, dstAddr);
			break;	
		}
		case(DHCPDECLINE): {
			DeclineHandler(server.transactionsStorage, client, server.addressesAllocator, server).handle(*dhcpMsg, options, dstAddr);
			break;	
		}
		case(DHCPRELEASE): {
			ReleaseHandler(server.transactionsStorage, client, server.addressesAllocator, server).handle(*dhcpMsg, options, dstAddr);
			break;	
		}
		case(DHCPINFORM): {
			InformHandler(server.transactionsStorage, client, server.addressesAllocator, server).handle(*dhcpMsg, options, dstAddr);
			break;	
		};
	}
}
