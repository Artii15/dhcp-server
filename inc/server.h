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
#include "sender.h"

class Server {
	public:
		Server(Config&, AddressesAllocator&, TransactionsStorage&);
		~Server();

		void listen();
		void save();

		uint32_t serverIp;
		libnet_t* lnetHandle;
		Sender* sender;

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
};

#endif
