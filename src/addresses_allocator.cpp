#include "../inc/addresses_allocator.h"

using namespace std;

AddressesAllocator::AddressesAllocator(Config& configToUse):config(configToUse) {
	const list<PoolDescriptor>& poolsDescriptors = config.getPoolsDescriptors();

	for(list<PoolDescriptor>::const_iterator descriptorsIt = poolsDescriptors.begin(); descriptorsIt != poolsDescriptors.end(); descriptorsIt++) {
		const PoolDescriptor& poolDescriptor = *descriptorsIt;
		AddressesPool* pool = new AddressesPool(poolDescriptor);

		addressesPools[pool->getNetworkAddress()] = pool;
	}
}

AddressesAllocator::~AddressesAllocator() {
	for(unordered_map<uint32_t, AddressesPool*>::iterator poolsIt = addressesPools.begin(); poolsIt != addressesPools.end(); poolsIt++) {
		delete poolsIt->second;
	}
}

AllocatedAddress& AddressesAllocator::allocateAddressFor(const Client& client) {
	if(client.identificationMethod == BASED_ON_HARDWARE) {
		return allocate(client.networkAddress, client.hardwareAddress, addressesPools[client.networkAddress]->getNext());
	}
	else {
		return allocate(client.networkAddress, client.specialId, addressesPools[client.networkAddress]->getNext());
	}
}

AllocatedAddress& AddressesAllocator::allocate(const uint32_t networkAddress, const HardwareAddress& hardwareAddress, const uint32_t ip) {
	AllocatedAddress& allocatedAddress = allocatedByHardware[networkAddress][hardwareAddress];
	fillAddress(networkAddress, ip, allocatedAddress);

	return allocatedAddress;
}

AllocatedAddress& AddressesAllocator::allocate(const uint32_t networkAddress, const ClientSpecialId& specialId, const uint32_t ip) {
	AllocatedAddress& allocatedAddress = allocatedBySpecialId[networkAddress][specialId];
	fillAddress(networkAddress, ip, allocatedAddress);

	return allocatedAddress;
}

void AddressesAllocator::fillAddress(uint32_t networkAddress, uint32_t ip, AllocatedAddress& allocatedAddress) {
	const PoolDescriptor& poolDescriptor = addressesPools[networkAddress]->descriptor;
	allocatedAddress.ipAddress = ip;
	allocatedAddress.mask = poolDescriptor.networkMask;
	allocatedAddress.dnsServers = &poolDescriptor.dnsServers;
	allocatedAddress.routers = &poolDescriptor.routers;
	allocatedAddress.leaseTime = poolDescriptor.leaseTime;
	allocatedAddress.allocationTime = time(NULL);
}

uint32_t AddressesAllocator::determineClientNetwork(uint32_t giaddr) {
	return !giaddr ? config.getNetworkAddress() : matchNetworkToAddress(giaddr);
}

uint32_t AddressesAllocator::matchNetworkToAddress(uint32_t address) {
	for(unordered_map<uint32_t, AddressesPool*>::iterator poolsIt = addressesPools.begin(); poolsIt != addressesPools.end(); poolsIt++) {
		uint32_t networkAddress = poolsIt->first;
		AddressesPool* pool = poolsIt->second;

		if(pool->mayContain(address)) {
			return networkAddress;
		}
	}
	throw runtime_error("Provided address does not belong to any known network!");
}

bool AddressesAllocator::hasClientAllocatedAddress(const Client& client) {
	if(client.identificationMethod == BASED_ON_HARDWARE) {
		return allocatedByHardware.find(client.networkAddress) != allocatedByHardware.end() 
				&& allocatedByHardware[client.networkAddress].find(client.hardwareAddress) != allocatedByHardware[client.networkAddress].end();
	}
	else {
		return allocatedBySpecialId.find(client.networkAddress) != allocatedBySpecialId.end() 
				&& allocatedBySpecialId[client.networkAddress].find(client.specialId) != allocatedBySpecialId[client.networkAddress].end();
	}
}

void AddressesAllocator::freeClientAddress(const Client& client) {
	if(hasClientAllocatedAddress(client)) {
		uint32_t freedIpAddress = (client.identificationMethod == BASED_ON_HARDWARE) ? free(client.networkAddress, client.hardwareAddress) 
			: free(client.networkAddress, client.specialId);
		addressesPools[client.networkAddress]->abandon(freedIpAddress);
	}
}

uint32_t AddressesAllocator::free(uint32_t networkAddress, const HardwareAddress& hardwareAddress) {
	uint32_t freedAddress = allocatedByHardware[networkAddress][hardwareAddress].ipAddress;
	allocatedByHardware[networkAddress].erase(hardwareAddress);

	return freedAddress;
}

uint32_t AddressesAllocator::free(uint32_t networkAddress, const ClientSpecialId& specialId) {
	uint32_t freedAddress = allocatedBySpecialId[networkAddress][specialId].ipAddress;
	allocatedBySpecialId[networkAddress].erase(specialId);

	return freedAddress;
}

AllocatedAddress& AddressesAllocator::getAllocatedAddress(const Client& client) {
	if(client.identificationMethod == BASED_ON_HARDWARE) {
		return allocatedByHardware[client.networkAddress][client.hardwareAddress];
	}
	else {
		return allocatedBySpecialId[client.networkAddress][client.specialId];
	}
}


void AddressesAllocator::freeClientAddressButLeaveUnavailable(const Client& client) {
	if(hasClientAllocatedAddress(client)) {
		(client.identificationMethod == BASED_ON_HARDWARE) ? free(client.networkAddress, client.hardwareAddress) : free(client.networkAddress, client.specialId);
	}
}
