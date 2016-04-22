#include "../inc/server.h"

#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>


Server::Server() {
	configureSocket();
}

void Server::configureSocket() {
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(struct sockaddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	struct servent* dhcpService = getservbyname("BOOTPS", "UDP");
	if(dhcpService == NULL) {
		throw "Could not find port for BOOTPS service on UDP protocol";
	}
	serverAddr.sin_port = dhcpService->s_port;

	int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	int nFoo = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&nFoo, sizeof(nFoo));

	bind(sock, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));
}

Server::~Server() {
	close(sock);
}
