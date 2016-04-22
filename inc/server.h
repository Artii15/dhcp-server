#ifndef SERVER_H
#define SERVER_H

#include <pcap/pcap.h>

class Server {
	private:
		char pcapErrbuf[PCAP_ERRBUF_SIZE];
		pcap_t* pcapHandle;

		bpf_u_int32 serverIpAddr, serverIpMask;

		void setPacketsFilter();

	public:
		Server(char* interfaceName = NULL);
		~Server();

		void listen();
};

#endif
