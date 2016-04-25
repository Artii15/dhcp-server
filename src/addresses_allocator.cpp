#include "../inc/addresses_allocator.h"

using namespace std;

AddressesAllocator::AddressesAllocator(Config& configToUse):config(configToUse) {
	const list<PoolDescriptor>& poolsDescriptors = config.getPoolsDescriptors();

	for(list<PoolDescriptor>::const_iterator descriptorsIt = poolsDescriptors.begin(); descriptorsIt != poolsDescriptors.end(); descriptorsIt++) {
		const PoolDescriptor& poolDescriptor = *descriptorsIt;

		uint32_t networkAddress = calculateNetworkAddress(poolDescriptor.startAddress, poolDescriptor.networkMask);
		addressesPools[networkAddress] = new AddressesPool(poolDescriptor);
	}
}

AddressesAllocator::~AddressesAllocator() {
	for(unordered_map<uint32_t, AddressesPool*>::iterator poolsIt = addressesPools.begin(); poolsIt != addressesPools.end(); poolsIt++) {
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
