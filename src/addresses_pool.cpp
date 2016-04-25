#include "../inc/addresses_pool.h"
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdexcept>

using namespace std;

AddressesPool::AddressesPool(const PoolDescriptor poolDescriptor):descriptor(poolDescriptor) {
	// Example pool string: 192.168.1.2:192.168.1.254:255.255.255.0:24
	/*
	istringstream segments(poolString);
	string buffer;

	struct in_addr address;

	getline(segments, buffer, ':');
	if(inet_aton(buffer.c_str(), &address) == 0) {
		throw runtime_error("Invalid start address");
	}
	startAddress = ntohl(address.s_addr);

	getline(segments, buffer, ':');
	if(inet_aton(buffer.c_str(), &address) == 0) {
		throw runtime_error("Invalid end address");
	}
	endAddress = ntohl(address.s_addr);

	getline(segments, buffer, ':');
	if(inet_aton(buffer.c_str(), &address) == 0) {
		throw runtime_error("Invalid mask");
	}
	networkMask = ntohl(address.s_addr);

	getline(segments, buffer);
	leaseTime = stoul(buffer);

	nextToAssign = startAddress;
	*/
	nextToAssign = descriptor.startAddress;
}

uint32_t AddressesPool::getNext() {
	uint32_t nextAddress = findAbandonedAddress() || generateFreshAddress();

	addressesInUse.insert(nextAddress);
	abandonedAddresses.erase(nextAddress);

	return nextAddress;
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

bool AddressesPool::isInUse(uint32_t address) {
	return addressesInUse.find(address) != addressesInUse.end();
}

void AddressesPool::abandon(uint32_t address) {
	addressesInUse.erase(address);
	abandonedAddresses.insert(address);
}

boost::regex AddressesPool::validPoolStringPattern = boost::regex("^(\\d{1,3}(\\.\\d{1,3}){3}:){3}\\d+$");
bool AddressesPool::isValidPoolString(const char* poolString) {
	return boost::regex_match(poolString, AddressesPool::validPoolStringPattern);
}
