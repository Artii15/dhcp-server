#ifndef ADDRESSES_ALLOCATOR_H
#define ADDRESSES_ALLOCATOR_H

#include "hardware_address.h"
#include "allocated_address.h"
#include "config.h"
#include "addresses_pool.h"
#include <stdint.h>
#include <unordered_map>

class AddressesAllocator {
	public:
		AddressesAllocator(Config& config);

		AllocatedAddress allocate();
		AllocatedAddress allocate(uint32_t networkAddress);
		AllocatedAddress allocate(const HardwareAddress& clientAddress, uint32_t networkAddress);
	private:
		Config& config;
		std::unordered_map<uint32_t, AddressesPool> addressesPools;
};

#endif
