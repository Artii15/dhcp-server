#include "../inc/addresses_allocator.h"

using namespace std;

AddressesAllocator::AddressesAllocator(Config& configToUse):config(configToUse) {
	const list<PoolDescriptor>& poolsDescriptors = config.getPoolsDescriptors();

	for(list<PoolDescriptor>::const_iterator descriptorsIt = poolsDescriptors.begin(); descriptorsIt != poolsDescriptors.end(); descriptorsIt++) {
		const PoolDescriptor& poolDescriptor = *descriptorsIt;

		addressesPools[calculateNetworkAddress(poolDescriptor.startAddress, poolDescriptor.networkMask)] = new AddressesPool(poolDescriptor);
	}
}

uint32_t AddressesAllocator::calculateNetworkAddress(uint32_t address, uint32_t mask) {
	return (address & mask);
}

AddressesAllocator::~AddressesAllocator() {
	for(unordered_map<uint32_t, AddressesPool*>::iterator poolsIt = addressesPools.begin(); poolsIt != addressesPools.end(); poolsIt++) {
		delete poolsIt->second;
	}
}

AllocatedAddress AddressesAllocator::allocate(const HardwareAddress& clientAddress, uint32_t giaddr) {

	return AllocatedAddress();	
}
