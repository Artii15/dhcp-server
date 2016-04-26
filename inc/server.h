#ifndef SERVER_H
#define SERVER_H

#include <pcap/pcap.h>
#include <libnet.h>
#include <unordered_map>
#include "options.h"
#include "transaction.h"
#include "addresses_allocator.h"
#include "config.h"

class Server {
	public:
		Server(AddressesAllocator &allocator, Config &config);
		~Server();

		void listen();

	private:
		Config &config;
		AddressesAllocator &addressesAllocator;

		static void dispatch(u_char *server, const struct pcap_pkthdr *header, const u_char *bytes);

		uint32_t determineDeviceIp(const char* interfaceName);

		char pcapErrbuf[PCAP_ERRBUF_SIZE];
		pcap_t* pcapHandle;
		uint32_t serverIp;

		char lnetErrbuf[LIBNET_ERRBUF_SIZE];
		libnet_t* lnetHandle;

		std::unordered_map<uint32_t, Transaction> transactions;

		void setPacketsFilter();

		void handleDiscover(struct DHCPMessage* dhcpMsg, Options* options);
		void sendOffer(DHCPMessage* dhcpMsg, const AllocatedAddress &allocatedAddress);
		uint8_t* packIpAddressLeaseTime(uint8_t* dst, uint32_t leaseTime);
		uint8_t* packMessageType(uint8_t* dst, uint8_t messageType);
		uint8_t* packServerIdentifier(uint8_t* dst);
		uint8_t* packNetworkMask(uint8_t* dst, uint32_t mask);
		uint8_t* packRouters(uint8_t* dst, const std::list<uint32_t>& routers);

		void handleRequest(struct DHCPMessage* dhcpMsg, Options* options);
		void sendAck(DHCPMessage* dhcpMsg, Transaction &transaction);

		bool transactionExists(uint32_t id);
};

#endif
