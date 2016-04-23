#include "../inc/server.h"
#include "../inc/dhcp_message.h"

#include <netdb.h>
#include <stdio.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define MAX_FILTER_SIZE 64

using namespace std;

Server::Server(Config& config) {
	const char* interfaceName = config.get("interface").c_str();
	pcapHandle = pcap_create(interfaceName, pcapErrbuf);
	if(pcapHandle == NULL) {
		throw pcapErrbuf;
	}
	pcap_set_snaplen(pcapHandle, 65535);
	if(pcap_activate(pcapHandle) != 0) {
		throw pcapErrbuf;
	}

	if(pcap_lookupnet(interfaceName, &serverIpAddr, &serverIpMask, pcapErrbuf) != 0) {
		throw pcapErrbuf;
	}

	setPacketsFilter();
	setServerIdetifier(interfaceName);
}

void Server::setPacketsFilter() {
	struct bpf_program fp;

	struct servent* bootpServerService = getservbyname("bootps", "udp");
	if(bootpServerService == NULL) {
		throw "Could determine bootps service port for udp";
	}
	uint16_t bootpServerPort = ntohs(bootpServerService->s_port);

	struct servent* bootpClientService = getservbyname("bootpc", "udp");
	if(bootpClientService == NULL) {
		throw "Could determine bootpc service port for udp";
	}
	uint16_t bootpClientPort = ntohs(bootpClientService->s_port);

	char filter[MAX_FILTER_SIZE] = {0};
	snprintf(filter, MAX_FILTER_SIZE - 1, "ether proto 0x%04x and udp dst port %u and udp src port %u", ETH_P_IP, bootpServerPort, bootpClientPort);
	if(pcap_compile(pcapHandle, &fp, filter, 0, serverIpMask) != 0) {
		throw pcapErrbuf;
	}
	if(pcap_setfilter(pcapHandle, &fp) < 0) {
		throw pcapErrbuf;
	}
}

void Server::setServerIdetifier(const char* serverInterface) {
	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	struct ifreq ifr;
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, serverInterface, IFNAMSIZ-1);
	ioctl(fd, SIOCGIFADDR, &ifr);

	close(fd);

	identifier = ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr;
}

Server::~Server() {
	pcap_close(pcapHandle); 
}

void Server::listen() {
	pcap_loop(pcapHandle, 0, &Server::dispatch, (u_char*)this);
}

void Server::dispatch(u_char *server, const struct pcap_pkthdr *header, const u_char *rawMessage) {
	struct ethhdr* layer2Header = (struct ethhdr*)rawMessage;
	printf("[%dB of %dB]\n", header->caplen, header->len);
	printf("source address %02x:%02x:%02x:%02x:%02x:%02x\n", layer2Header->h_source[0], layer2Header->h_source[1], layer2Header->h_source[2], layer2Header->h_source[3], layer2Header->h_source[4], layer2Header->h_source[5]);
	
	unsigned int dhcpMsgStartPos = sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr);
	struct DHCPMessage* dhcpMsg = (struct DHCPMessage*)(rawMessage + dhcpMsgStartPos);
	Options options(dhcpMsg->options, header->caplen - dhcpMsgStartPos);	

	uint8_t operationType = *options.get(DHCP_MESSAGE_TYPE).value;
	switch(operationType) {
		case(DHCPDISCOVER): {
			((Server*)server)->handleDiscover(dhcpMsg, &options);
			break;	
		}
		case(DHCPREQUEST): {
			printf("%u\n", operationType);
			break;	
		}
	}
}

void Server::handleDiscover(struct DHCPMessage* dhcpMsg, Options* options) {
	if(!transactionExists(dhcpMsg->xid)) {
		Transaction transaction(dhcpMsg->xid, 3232235876, 1000000000);
		transactions[dhcpMsg->xid] = transaction;
	}
}

void Server::sendOffer(struct DHCPMessage* dhcpMsg, Transaction &transaction) {
	DHCPMessage offer;		
	memset(&offer, 0, sizeof(offer));

	offer.op = BOOTREPLY;
	offer.htype = dhcpMsg->htype;
	offer.hlen = dhcpMsg->hlen;
	offer.xid = dhcpMsg->xid;
	offer.yiaddr = transaction.allocatedIpAddress;
	offer.flags = dhcpMsg->flags;
	offer.giaddr = dhcpMsg->giaddr;
	memcpy(offer.chaddr, dhcpMsg->chaddr, MAX_HADDR_SIZE);
	offer.magicCookie = dhcpMsg->magicCookie;

	uint8_t* optionsPtr = packIpAddressLeaseTime(offer.options, transaction.leaseTime);
	optionsPtr = packMessageType(optionsPtr, DHCPOFFER);
}

uint8_t* Server::packIpAddressLeaseTime(uint8_t* dst, uint32_t leaseTime) {
	*(dst++) = IP_ADDRESS_LEASE_TIME;
	*(dst++) = sizeof(leaseTime);

	uint32_t normalizedLeaseTime = htonl(leaseTime);
	memcpy(dst, &normalizedLeaseTime, sizeof(normalizedLeaseTime));

	return dst + sizeof(normalizedLeaseTime);
}

uint8_t* Server::packMessageType(uint8_t* dst, uint8_t messageType) {
	*(dst++) = DHCP_MESSAGE_TYPE;
	*(dst++) = sizeof(messageType);
	*(dst++) = messageType;

	return dst;
}

uint8_t* Server::packServerIdentifier(uint8_t* dst) {

	return dst;
}

bool Server::transactionExists(uint32_t id) {
	unordered_map<uint32_t, Transaction>::iterator transactionsIterator = transactions.find(id);

	return transactionsIterator != transactions.end();
}
