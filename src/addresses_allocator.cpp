#include "../inc/addresses_allocator.h"

using namespace std;

AddressesAllocator::AddressesAllocator(Config& configToUse):config(configToUse) {
	const list<PoolDescriptor>& poolsDescriptors = config.getPoolsDescriptors();

	for(list<PoolDescriptor>::iterator descriptorsIt; descriptorsIt != poolsDescriptors.end(); descriptorsIt++) {
		PoolDescriptor& poolDescriptor = *descriptorsIt;
		addressesPools[calculateNetworkAddress(poolDescriptor.startAddress, poolDescriptor.networkMask)] = new AddressesPool(poolDescriptor);
	}
}

AddressesAllocator::~AddressesAllocator() {
	for(unordered_map<uint32_t, AddressesPool*>::iterator poolsIt; poolsIt != addressesPools.end(); poolsIt++) {
		delete poolsIt->second;
	}
}

uint32_t AddressesAllocator::calculateNetworkAddress(uint32_t address, uint32_t mask) {
	return address & mask;
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
