#ifndef ADDRESSES_POOL_H
#define ADDRESSES_POOL_H

#include <stdint.h>
#include <unordered_set>

class AddressesPool {
	public:
		AddressesPool(const char* poolString);
		uint32_t getNext();
		bool isInUse(uint32_t address);

	private:
		uint32_t startAddress;
		uint32_t endAddress;
		uint32_t nextToAssign;
		uint32_t networkMask;
		uint32_t leaseTime;

		std::unordered_set<uint32_t> addressesInUse;
		std::unordered_set<uint32_t> abandonedAddresses;

		uint32_t findAbandonedAddress();
};

#endif
