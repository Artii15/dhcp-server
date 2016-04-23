#ifndef OPTION_H
#define OPTION_H

#include <stdint.h>

#define DHCP_MESSAGE_TYPE 53
#define DHCPDISCOVER 1
#define DHCPOFFER 2
#define DHCPREQUEST 3

struct Option {
	uint8_t code;
	uint8_t length;
	uint8_t* value;
};

#endif
