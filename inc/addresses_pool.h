#ifndef ADDRESSES_POOL_H
#define ADDRESSES_POOL_H

#include <string>

class AddressesPool {
	public:
		std::string getAddressFor(const char* mac);
};

#endif
