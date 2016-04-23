#ifndef DHCP_MESSAGE_H
#define DHCP_MESSAGE_H

#include <stdint.h>

#define MAX_HADDR_SIZE 16
#define MAX_SERVER_NAME_SIZE 64
#define MAX_BOOT_FILE_NAME_SIZE 128
#define MAX_OPTIONS_SIZE 312

#define BOOTREQUEST 1

struct DHCPMessage {
	uint8_t op;
	uint8_t htype;
	uint8_t hlen;
	uint8_t hops;
	uint32_t xid;
	uint16_t secs;
	uint16_t flags;
	uint32_t ciaddr;
	uint32_t yiaddr;
	uint32_t siaddr;
	uint32_t giaddr;
	uint8_t chaddr[MAX_HADDR_SIZE];
	uint8_t sname[MAX_SERVER_NAME_SIZE];
	uint8_t file[MAX_BOOT_FILE_NAME_SIZE];
	uint8_t options[MAX_OPTIONS_SIZE];
} __attribute__((packed));

#endif
