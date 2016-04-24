#include "../inc/protocol.h"

#include <netdb.h>
#include <arpa/inet.h>
#include <cstddef>

uint16_t Protocol::getServicePortByName(const char* serviceName, const char* protocolName) {
	struct servent* service = getservbyname(serviceName, protocolName);
	if(service == NULL) {
		throw "Service not recognized";
	}

	return ntohs(service->s_port);
}
