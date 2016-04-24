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
		uint32_t lastAssigned;
		uint32_t networkMask;
		
		std::unordered_set<uint32_t> addressesInUse;
};

#endif
