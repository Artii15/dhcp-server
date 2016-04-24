#include "../inc/addresses_pool.h"
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdexcept>

using namespace std;

AddressesPool::AddressesPool(const char* poolString) {
	// Example pool string: 192.168.1.2:192.168.1.254:255.255.255.0:24
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
}

uint32_t AddressesPool::getNext() {
	return nextToAssign++;
}

bool AddressesPool::isInUse(uint32_t address) {
	return addressesInUse.find(address) != addressesInUse.end();
}
