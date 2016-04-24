#ifndef ADDRESSES_ALLOCATOR_H
#define ADDRESSES_ALLOCATOR_H

#include "hardware_address.h"
#include <stdint.h>

class AddressesAllocator {
	public:
		bool allocate(const HardwareAddress& clientAddress, uint32_t ipAddress);
};

#endif
