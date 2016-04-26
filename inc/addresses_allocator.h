#ifndef ADDRESSES_ALLOCATOR_H
#define ADDRESSES_ALLOCATOR_H

#include "hardware_address.h"
#include "allocated_address.h"
#include "config.h"
#include "addresses_pool.h"
#include <stdint.h>
#include <unordered_map>
#include <map>

class AddressesAllocator {
	public:
		AddressesAllocator(Config& config);
		~AddressesAllocator();

		AllocatedAddress allocate(const HardwareAddress& clientAddress, uint32_t giaddr, uint32_t preferedAddress);
	private:
		Config& config;
		std::unordered_map<uint32_t, AddressesPool*> addressesPools;
		std::map<HardwareAddress, AllocatedAddress> allocatedAddresses;

		uint32_t determineClientNetwork(uint32_t giaddr);
		uint32_t matchNetworkToAddress(uint32_t address);
};

#endif
