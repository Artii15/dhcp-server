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

AllocatedAddress AddressesAllocator::allocate(const HardwareAddress& clientAddress, uint32_t giaddr, uint32_t preferedAddress) {
		
	return AllocatedAddress();
}

uint32_t AddressesAllocator::determineClientNetwork(uint32_t giaddr) {
	return !giaddr ? config.getNetworkAddress() : matchNetworkToAddress(giaddr);
}

uint32_t AddressesAllocator::matchNetworkToAddress(uint32_t address) {
	for(unordered_map<uint32_t, AddressesPool*>::iterator poolsIt = addressesPools.begin(); poolsIt != addressesPools.end(); poolsIt++) {
		uint32_t networkAddress = poolsIt->first;
		uint32_t networkMask = poolsIt->second->getNetworkMask();

		if(calculateNetworkAddress(address, networkMask) == networkAddress) {
			return networkAddress;
		}
	}
	throw runtime_error("Provided address does not belong to any known network!");
}
