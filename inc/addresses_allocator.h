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

		AllocatedAddress& allocateAddressFor(const Client& client);
		bool hasClientAllocatedAddress(const Client&);
		void freeClientAddress(const Client& client);
		AllocatedAddress& getAllocatedAddress(const Client& client);

	private:
		Config& config;
		std::unordered_map<uint32_t, AddressesPool*> addressesPools;
		std::map<uint32_t, std::map<HardwareAddress, AllocatedAddress> > allocatedByHardware;
		std::map<uint32_t, std::map<ClientSpecialId, AllocatedAddress> > allocatedBySpecialId;

		AllocatedAddress& allocate(const uint32_t networkAddress, const HardwareAddress& hardwareAddress, const uint32_t address);
		AllocatedAddress& allocate(const uint32_t networkAddress, const ClientSpecialId& specialId, const uint32_t address);
		void fillAddress(uint32_t networkAddress, uint32_t ip, AllocatedAddress&);

		uint32_t determineClientNetwork(uint32_t giaddr);
		uint32_t matchNetworkToAddress(uint32_t address);

		uint32_t free(uint32_t networkAddress, const HardwareAddress&);
		uint32_t free(uint32_t networkAddress, const ClientSpecialId&);
};

#endif
