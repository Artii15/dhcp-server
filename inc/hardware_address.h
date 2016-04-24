#ifndef HARDWARE_ADDRESS_H
#define HARDWARE_ADDRESS_H

#include "dhcp_message.h"
#include <string.h>

struct HardwareAddress {
	uint8_t addressType;
	uint8_t hardwareAddress[MAX_HADDR_SIZE];

	inline bool operator == (const HardwareAddress &address) const {
        return (addressType == address.addressType && (memcmp(hardwareAddress, address.hardwareAddress, MAX_HADDR_SIZE) == 0));
    }
};

#endif
