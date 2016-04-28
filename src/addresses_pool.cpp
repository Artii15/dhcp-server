#include "../inc/addresses_pool.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string>
#include <stdexcept>

using namespace std;

AddressesPool::AddressesPool(const PoolDescriptor& poolDescriptor): descriptor(poolDescriptor) {
	nextToAssign = descriptor.startAddress;
	networkAddress = calculateNetworkAddress(descriptor.startAddress, descriptor.networkMask);
}

bool AddressesPool::mayContain(uint32_t address) {
	return calculateNetworkAddress(address, descriptor.networkMask) == networkAddress;
}

uint32_t AddressesPool::calculateNetworkAddress(uint32_t address, uint32_t mask) {
	return (address & mask);
}

uint32_t AddressesPool::getNext() {
	uint32_t address = findAbandonedAddress();

	return address ? address : generateFreshAddress();
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
