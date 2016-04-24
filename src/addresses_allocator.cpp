#include "../inc/addresses_allocator.h"

AllocatedAddress AddressesAllocator::allocate() {
	return AllocatedAddress();	
}

AllocatedAddress AddressesAllocator::allocate(uint32_t networkAddress) {
	return AllocatedAddress();	
}

AllocatedAddress AddressesAllocator::allocate(const HardwareAddress& clientAddress, uint32_t networkAddress) {
	return AllocatedAddress();	
}
