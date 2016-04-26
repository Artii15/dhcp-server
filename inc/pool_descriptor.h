#ifndef POOL_DESCRIPTOR_H
#define POOL_DESCRIPTOR_H

#include <stdint.h>
#include <list>

struct PoolDescriptor {
	uint32_t startAddress;
	uint32_t endAddress;
	uint32_t networkMask;
	uint32_t leaseTime;
	uint32_t dnsAddress;
	std::list<uint32_t> routers;
};

#endif
