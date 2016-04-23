#ifndef SERVER_H
#define SERVER_H

#include <pcap/pcap.h>
#include "config.h"

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

		void setPacketsFilter();
};

#endif
