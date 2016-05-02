#ifndef HARDWARE_ADDRESS_H
#define HARDWARE_ADDRESS_H

#include "dhcp_message.h"
#include "bytes_comparator.h"
#include <string.h>

struct HardwareAddress {
	uint8_t addressType;
	uint8_t hardwareAddress[MAX_HADDR_SIZE];

	HardwareAddress() {}

	HardwareAddress(const HardwareAddress& address): HardwareAddress(address.addressType, address.hardwareAddress) {}

	HardwareAddress(const uint8_t addressType, const uint8_t* hardwareAddress) {
		this->addressType = addressType;
		memcpy(this->hardwareAddress, hardwareAddress, MAX_HADDR_SIZE);
	}

	inline bool operator < (const HardwareAddress &address) const {
        return (addressType < address.addressType) || (addressType == address.addressType && BytesComparator::compareArrays(hardwareAddress, address.hardwareAddress, MAX_HADDR_SIZE) < 0);
    }
};

#endif
