#ifndef CLIENT_ID_H
#define CLIENT_ID_H

#include "dhcp_message.h"

struct ClientId {
	uint8_t addressType;
	uint8_t hardwareAddress[MAX_HADDR_SIZE];
};

#endif
