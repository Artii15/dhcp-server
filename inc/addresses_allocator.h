#ifndef ADDRESSES_ALLOCATOR_H
#define ADDRESSES_ALLOCATOR_H

#include "hardware_address.h"
#include "allocated_address.h"
#include "config.h"
#include "addresses_pool.h"
#include <stdint.h>

class AddressesAllocator {
	public:
		AddressesAllocator(Config& config, AddressesPool& addressesPool);

		AllocatedAddress allocate();
		AllocatedAddress allocate(uint32_t networkAddress);
		AllocatedAddress allocate(const HardwareAddress& clientAddress, uint32_t networkAddress);
};

#endif
