#ifndef OPTION_H
#define OPTION_H

#include <stdint.h>

#define DHCPDISCOVER 1
#define DHCPOFFER 2
#define DHCPREQUEST 3
#define DHCPACK 5

#define SUBNET_MASK 1
#define IP_ADDRESS_LEASE_TIME 51
#define DHCP_MESSAGE_TYPE 53
#define SERVER_IDENTIFIER 54
#define END_OPTION 255

struct Option {
	uint8_t code;
	uint8_t length;
	uint8_t* value;
};

#endif
