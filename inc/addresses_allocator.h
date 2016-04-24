#ifndef ADDRESSES_ALLOCATOR_H
#define ADDRESSES_ALLOCATOR_H

#include "dhcp_message.h"
#include <stdint.h>

class AddressesAllocator {
	public:
		bool allocate(uint32_t hostIp, uint32_t networkIp);
};

#endif
