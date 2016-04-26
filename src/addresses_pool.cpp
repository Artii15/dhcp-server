#include "../inc/addresses_pool.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdexcept>

using namespace std;

AddressesPool::AddressesPool(const PoolDescriptor& poolDescriptor):descriptor(poolDescriptor) {
	nextToAssign = descriptor.startAddress;
	networkAddress = calculateNetworkAddress(descriptor.startAddress, descriptor.networkMask);
}

bool AddressesPool::mayContain(uint32_t address) {
	return calculateNetworkAddress(address, descriptor.networkMask) == networkAddress;
}

uint32_t AddressesPool::calculateNetworkAddress(uint32_t address, uint32_t mask) {
	return (address & mask);
}

AllocatedAddress AddressesPool::getNext() {
	AllocatedAddress allocatedAddress;
	if((allocatedAddress.ipAddress = findAbandonedAddress()) == 0) {
		allocatedAddress.ipAddress = generateFreshAddress();
	}
	allocatedAddress.mask = descriptor.networkMask;
	allocatedAddress.routerAddress = descriptor.routerAddress;
	allocatedAddress.dnsAddress = descriptor.dnsAddress;
	allocatedAddress.leaseTime = descriptor.leaseTime;

	addressesInUse.insert(allocatedAddress.ipAddress);
	abandonedAddresses.erase(allocatedAddress.ipAddress);

	return allocatedAddress;
}

uint32_t AddressesPool::generateFreshAddress() {
	if(nextToAssign > descriptor.endAddress) {
		throw runtime_error("No more addresses to assign");
	}
	return nextToAssign++;
}

uint32_t AddressesPool::findAbandonedAddress() {
	return (abandonedAddresses.begin() == abandonedAddresses.end()) ? 0 : *abandonedAddresses.begin();
}

void AddressesPool::abandon(uint32_t address) {
	addressesInUse.erase(address);
	abandonedAddresses.insert(address);
}

uint32_t AddressesPool::getNetworkAddress() {
	return networkAddress;
}
