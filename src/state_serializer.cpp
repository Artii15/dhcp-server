#include "../inc/state_serializer.h"
#include <stdio.h>

using namespace std;

StateSerializer::StateSerializer(const char* filePath) {
	remove(filePath);
	file = fopen(filePath, "wb");
}

StateSerializer::~StateSerializer() {
	fclose(file);
}

void StateSerializer::serialize(const AllocatedAddress& address) {
	serialize(address.ipAddress);
	serialize(address.mask);
	serialize(address.leaseTime);
	serializeTime(address.allocationTime);
	
	serialize(address.dnsServers);
	serialize(address.routers);
}

void StateSerializer::serialize(const list<uint32_t>& uint32List) {
	serialize(uint32List.size());

	for(list<uint32_t>::const_iterator it = uint32List.begin(); it != uint32List.end(); it++) {
		fwrite(&*it, sizeof(uint32_t), 1, file);
	}
}

void StateSerializer::serialize(const HardwareAddress& hardwareAddress) {
	fwrite(&hardwareAddress.addressType, sizeof(uint8_t), 1, file);
	fwrite(&hardwareAddress.hardwareAddress, sizeof(uint8_t), MAX_HADDR_SIZE, file);
}

void StateSerializer::serialize(const ClientSpecialId& specialId) {
	fwrite(&specialId.type, sizeof(uint8_t), 1, file);
	fwrite(&specialId.value, sizeof(uint8_t), CLIENT_SPECIAL_ID_MAX_LEN, file);
}

void StateSerializer::serialize(const uint32_t value) {
	fwrite(&value, sizeof(value), 1, file);
}

void StateSerializer::serializeTime(const time_t value) {
	fwrite(&value, sizeof(value), 1, file);
}

void StateSerializer::serialize(const AddressesPool& pool) {
	fwrite(&pool.networkAddress, sizeof(pool.networkAddress), 1, file);
	fwrite(&pool.nextToAssign, sizeof(pool.nextToAssign), 1, file);

	serialize(pool.abandonedAddresses);
}

void StateSerializer::serialize(const std::unordered_set<uint32_t>& uint32Set) {
	serialize(uint32Set.size());
	for(unordered_set<uint32_t>::const_iterator it = uint32Set.begin(); it != uint32Set.end(); it++) {
		fwrite(&*it, sizeof(uint32_t), 1, file);
	}
}
