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

size_t StateDeserializer::deserialize(list<uint32_t>* uint32List) {
	uint32_t listSize = 0;
	deserialize(&listSize);

	size_t bytesReaded = 0;
	for(unsigned i = 0; i < listSize; ++i) {
		uint32_t element;
		bytesReaded += fread(&element, sizeof(uint32_t), 1, file);
		uint32List->push_back(element);
	}

	return bytesReaded;
}

size_t StateDeserializer::deserialize(uint32_t* target) {
	return fread(target, sizeof(uint32_t), 1, file);
}

size_t StateDeserializer::deserialize(long int* target) {
	return fread(target, sizeof(long int), 1, file);
}


size_t StateDeserializer::deserialize(HardwareAddress* hardwareAddress) {
	return fread(&hardwareAddress->addressType, sizeof(uint8_t), 1, file) 
		+ fread(hardwareAddress->hardwareAddress, sizeof(uint8_t), MAX_HADDR_SIZE, file);
}

void StateDeserializer::deserialize(ClientSpecialId*) {

}
