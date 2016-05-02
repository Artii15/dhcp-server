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

void StateDeserializer::deserialize(AllocatedAddress* address) {
	deserialize(&address->ipAddress);
	deserialize(&address->mask);
	deserialize(&address->leaseTime);
	deserialize(&address->allocationTime);
	
	//deserialize(address->dnsServers);
	//deserialize(address->routers);
}

size_t StateDeserializer::deserialize(uint32_t* target) {
	return fread(target, sizeof(uint32_t), 1, file);
}

size_t StateDeserializer::deserialize(long int* target) {
	return fread(target, sizeof(long int), 1, file);
}


void StateDeserializer::deserialize(HardwareAddress* hardwareAddress) {

}

void StateDeserializer::deserialize(ClientSpecialId*) {

}
