#ifndef SERVER_H
#define SERVER_H

#include <pcap/pcap.h>
#include <libnet.h>
#include <unordered_map>
#include "options.h"
#include "addresses_allocator.h"
#include "config.h"
#include "transactions_storage.h"
#include "network_resolver.h"

class Server {
	public:
		Server(Config&, AddressesAllocator&, TransactionsStorage&);
		~Server();

		void listen();

		uint32_t serverIp;
		libnet_t* lnetHandle;

	private:
		Config &config;
		AddressesAllocator &addressesAllocator;
		TransactionsStorage &transactionsStorage;
		NetworkResolver* networkResolver;

		static void dispatch(u_char *server, const struct pcap_pkthdr *header, const u_char *bytes);

		uint32_t determineDeviceIp(const char* interfaceName);

		char pcapErrbuf[PCAP_ERRBUF_SIZE];
		pcap_t* pcapHandle;

		char lnetErrbuf[LIBNET_ERRBUF_SIZE];

		void setPacketsFilter();

		uint8_t* packIpAddressLeaseTime(uint8_t* dst, uint32_t leaseTime);
		uint8_t* packMessageType(uint8_t* dst, uint8_t messageType);
		uint8_t* packServerIdentifier(uint8_t* dst);
		uint8_t* packNetworkMask(uint8_t* dst, uint32_t mask);
		uint8_t* packRouters(uint8_t* dst, const std::list<uint32_t>* routers);
		uint8_t* packDnsServers(uint8_t* dst, const std::list<uint32_t>* servers);

		void handleRequest(struct DHCPMessage* dhcpMsg, Options* options);
		void sendAck(DHCPMessage* dhcpMsg, const AllocatedAddress &allocatedAddress);
};

#endif
