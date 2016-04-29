#ifndef ADDRESSES_ALLOCATOR_H
#define ADDRESSES_ALLOCATOR_H

#include "hardware_address.h"
#include "client_special_id.h"
#include "allocated_address.h"
#include "config.h"
#include "addresses_pool.h"
#include "client.h"
#include <stdint.h>
#include <unordered_map>
#include <map>

class AddressesAllocator {
	public:
		AddressesAllocator(Config& config);
		~AddressesAllocator();

		AllocatedAddress allocate(const HardwareAddress& clientAddress, uint32_t giaddr, uint32_t preferedAddress);
		AllocatedAddress reallocateOldAddress(const Client& client);
		AllocatedAddress allocateNewAddress(const Client& client);
		bool hasClientAllocatedAddress(const Client&);
	private:
		Config& config;
		std::unordered_map<uint32_t, AddressesPool*> addressesPools;
		std::map<uint32_t, std::map<HardwareAddress, AllocatedAddress> > allocatedByHardware;
		std::map<uint32_t, std::map<ClientSpecialId, AllocatedAddress> > allocatedBySpecialId;

		void allocate(uint32_t networkAddress, HardwareAddress& hardwareAddress, uint32_t address);
		void allocate(uint32_t networkAddress, ClientSpecialId& specialId, uint32_t address);

		uint32_t determineClientNetwork(uint32_t giaddr);
		uint32_t matchNetworkToAddress(uint32_t address);
};

#endif
