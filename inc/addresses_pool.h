#ifndef ADDRESSES_POOL_H
#define ADDRESSES_POOL_H

#include <stdint.h>
#include <set>

class AddressesPool {
	public:
		uint32_t startAddress;
		uint32_t endAddress;
		uint32_t lastAssigned;
		uint32_t networkMask;
		
		std::set<uint32_t> addressesInUse;
};

#endif
