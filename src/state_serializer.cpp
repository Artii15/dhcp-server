#include "../inc/state_serializer.h"
#include <stdio.h>

StateSerializer::StateSerializer(const char* filePath) {
	remove(filePath);
	file = fopen(filePath, "wb");
}

StateSerializer::~StateSerializer() {
	fclose(file);
}

void StateSerializer::serialize(const AllocatedAddress& allocatedAddress) {
/*
	for(map<HardwareAddress, AllocatedAddress> >::const_iterator it = allocatedByHardware.begin(); it != allocatedByHardware.end(); it++) {
		const AllocatedAddress& address = *it;
		fwrite(&address.ipAddress, sizeof(address.ipAddress), 1, file);
		fwrite(&address.mask, sizeof(address.mask), 1, file);
		fwrite(&address.leaseTime, sizeof(address.leaseTime), 1, file);
		fwrite(&address.allocationTime, sizeof(address.allocationTime), 1, file);
		fwrite(&address.allocationTime, sizeof(address.allocationTime), 1, file);

	}

	const std::list<uint32_t>* dnsServers;
	const std::list<uint32_t>* routers;
*/
}

void StateSerializer::serialize(const unsigned value) {
	fwrite(&value, sizeof(value), 1, file);
}

void StateSerializer::serialize(const HardwareAddress& hardwareAddress) {

}
