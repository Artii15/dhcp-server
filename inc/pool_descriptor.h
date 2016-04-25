#ifndef POOL_DESCRIPTOR_H
#define POOL_DESCRIPTOR_H

#include <stdint.h>

struct PoolDescriptor {
	uint32_t startAddress;
	uint32_t endAddress;
	uint32_t networkMask;
	uint32_t leaseTime;
	uint32_t dnsAddress;
	uint32_t routerAddress;
};

#endif
