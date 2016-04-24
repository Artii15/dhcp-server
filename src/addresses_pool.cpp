#include "../inc/addresses_pool.h"

AddressesPool::AddressesPool(const char* poolString) {

}

uint32_t AddressesPool::getNext() {
	return 1;
}

bool AddressesPool::isInUse(uint32_t address) {
	return addressesInUse.find(address) != addressesInUse.end();
}
