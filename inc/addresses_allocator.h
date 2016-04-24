#ifndef ADDRESSES_ALLOCATOR_H
#define ADDRESSES_ALLOCATOR_H

#include "hardware_address.h"
#include <stdint.h>

class AddressesAllocator {
	public:
		uint32_t allocate(const HardwareAddress& clientAddress, uint32_t networkAddress);
};

#endif
