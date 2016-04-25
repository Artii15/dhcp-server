#include "../inc/addresses_allocator.h"

using namespace std;

AddressesAllocator::AddressesAllocator(Config& configToUse):config(configToUse) {
		
}

AllocatedAddress AddressesAllocator::allocate() {
	return AllocatedAddress();	
}

AllocatedAddress AddressesAllocator::allocate(uint32_t networkAddress) {
	return AllocatedAddress();	
}

AllocatedAddress AddressesAllocator::allocate(const HardwareAddress& clientAddress, uint32_t networkAddress) {
	return AllocatedAddress();	
}
