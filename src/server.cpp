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
	configureAddress(&serverAddr);

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	int nFoo = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&nFoo, sizeof(nFoo));
	bind(sock, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));
}

void Server::configureAddress(struct sockaddr_in* addr) {
	memset(addr, 0, sizeof(struct sockaddr));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;

	struct servent* dhcpService = getservbyname("BOOTPS", "UDP");
	if(dhcpService == NULL) {
		throw "Could not find port for BOOTPS service on UDP protocol";
	}
	addr->sin_port = dhcpService->s_port;
}

Server::~Server() {
	close(sock);
}
