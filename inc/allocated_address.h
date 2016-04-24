#ifndef ALLOCATED_ADDRESS_H
#define ALLOCATED_ADDRESS_H

#include <stdint.h>

struct AllocatedAddress {
	uint32_t ipAddress;
	uint32_t networkMask;

	inline bool operator == (const AllocatedAddress &address) const {
        return (ipAddress == address.ipAddress && networkMask == address.networkMask);
    }
};

#endif
