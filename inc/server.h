#ifndef SERVER_H
#define SERVER_H

#include <pcap/pcap.h>
#include <unordered_map>
#include "config.h"
#include "options.h"
#include "transaction.h"

class Server {
	public:
		Server(Config &config);
		~Server();

		void listen();

	private:
		static void dispatch(u_char *server, const struct pcap_pkthdr *header, const u_char *bytes);

		char pcapErrbuf[PCAP_ERRBUF_SIZE];
		pcap_t* pcapHandle;
		bpf_u_int32 serverIpAddr, serverIpMask;
		std::unordered_map<uint32_t, Transaction> transactions;

		void setPacketsFilter();
		void handleDiscover(struct DHCPMessage* dhcpMsg, Options* options);
		void sendOffer(DHCPMessage* dhcpMsg, Transaction &transaction);

		bool transactionExists(uint32_t id);
};

#endif
