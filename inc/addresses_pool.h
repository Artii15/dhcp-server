#ifndef ADDRESSES_POOL_H
#define ADDRESSES_POOL_H

#include <stdint.h>
#include <unordered_set>
#include "pool_descriptor.h"

class StateSerializer;
class StateDeserializer;

class AddressesPool {
	friend class StateSerializer;
	friend class StateDeserializer;
	public:
		AddressesPool(const PoolDescriptor&);

		uint32_t getNext();
		void abandon(uint32_t address);

		uint32_t getNetworkAddress();
		bool mayContain(uint32_t address);

		const PoolDescriptor descriptor;

	private:
		uint32_t networkAddress;
		uint32_t nextToAssign;

		std::unordered_set<uint32_t> abandonedAddresses;

		uint32_t findAbandonedAddress();
		uint32_t generateFreshAddress();
		uint32_t calculateNetworkAddress(uint32_t address, uint32_t mask);
};

#endif
