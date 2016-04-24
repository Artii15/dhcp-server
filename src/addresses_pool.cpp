#include "../inc/addresses_pool.h"
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

using namespace std;

AddressesPool::AddressesPool(const char* poolString) {
	// Example pool string: 192.168.1.2:192.168.1.254:255.255.255.0:24
	istringstream segments(poolString);

	string buffer;
	getline(segments, buffer, ':');
	inet_aton(buffer.c_str(), (struct in_addr*)&startAddress);
}

uint32_t AddressesPool::getNext() {
	return 1;
}

bool AddressesPool::isInUse(uint32_t address) {
	return addressesInUse.find(address) != addressesInUse.end();
}
