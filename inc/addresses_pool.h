#ifndef ADDRESSES_POOL_H
#define ADDRESSES_POOL_H

#include <stdint.h>
#include <unordered_set>
#include "pool_descriptor.h"

class AddressesPool {
	public:
		AddressesPool(const PoolDescriptor);

		uint32_t getNext();
		void abandon(uint32_t address);
		bool isInUse(uint32_t address);

	private:
		const PoolDescriptor descriptor;
		uint32_t nextToAssign;

		std::unordered_set<uint32_t> addressesInUse;
		std::unordered_set<uint32_t> abandonedAddresses;

		uint32_t findAbandonedAddress();
		uint32_t generateFreshAddress();
};

#endif
