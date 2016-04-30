#ifndef OPTION_H
#define OPTION_H

#include <stdint.h>

#define DHCPDISCOVER 1
#define DHCPOFFER 2
#define DHCPREQUEST 3
#define DHCPDECLINE 4
#define DHCPACK 5
#define DHCPNAK 6
#define DHCPRELEASE 7
#define DHCPINFORM 8

#define SUBNET_MASK 1
#define ROUTERS 3
#define DNS_OPTION 6
#define REQUESTED_IP_ADDRESS 50
#define IP_ADDRESS_LEASE_TIME 51
#define DHCP_MESSAGE_TYPE 53
#define SERVER_IDENTIFIER 54
#define CLIENT_IDENTIFIER 61
#define END_OPTION 255

struct Option {
	uint8_t code;
	uint8_t length;
	uint8_t* value;
};

#endif
