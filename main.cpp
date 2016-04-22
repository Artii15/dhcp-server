#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>

int main(int argc, char** argv) {
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(struct sockaddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	struct servent* dhcpService = getservbyname("BOOTPS", "UDP");
	if(dhcpService == NULL) {
		perror("Error");	
		exit(EXIT_FAILURE);
	}
	serverAddr.sin_port = dhcpService->s_port;

	int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	int nFoo = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&nFoo, sizeof(nFoo));

	bind(sock, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));
	//while(1) {
		//recvfrom(
		//sendto
	//}

	close(sock);		

	return 0;
}
