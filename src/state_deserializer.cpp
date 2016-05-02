#include "../inc/state_deserializer.h"
#include <stdio.h>

using namespace std;

bool StateDeserializer::cacheExists(const char* filePath) {
	FILE *file;
    if((file = fopen(filePath, "r")) != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

StateDeserializer::StateDeserializer(const char* filePath) {
	file = fopen(filePath, "rb");
}

StateDeserializer::~StateDeserializer() {
	fclose(file);
}

size_t StateDeserializer::deserialize(uint32_t* target) {
	return fread(target, sizeof(uint32_t), 1, file);
}

size_t StateDeserializer::deserialize(AllocatedAddress* address) {
	size_t addrLen = fread(&address->ipAddress, sizeof(address->ipAddress), 1, file);
	size_t maskLen = fread(&address->mask, sizeof(address->mask), 1, file);
	size_t leaseTimeLen = fread(&address->leaseTime, sizeof(address->leaseTime), 1, file);
	size_t allocationTimeLen = fread(&address->allocationTime, sizeof(address->allocationTime), 1, file);
	
	//deserialize(address->dnsServers);
	//deserialize(address->routers);

	return addrLen + maskLen + leaseTimeLen + allocationTimeLen;
}

void StateDeserializer::deserialize(HardwareAddress* hardwareAddress) {

}

void StateDeserializer::deserialize(ClientSpecialId*) {

}
