#ifndef ALLOCATED_ADDRESS_H
#define ALLOCATED_ADDRESS_H

#include <stdint.h>
#include "pool_descriptor.h"

struct AllocatedAddress {
	uint32_t ipAddress;
	uint32_t mask;
	uint32_t routerAddress;
	uint32_t dnsAddress;
};

#endif
