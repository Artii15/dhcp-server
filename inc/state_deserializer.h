#ifndef STATE_DESERIALIZER_H
#define STATE_DESERIALIZER_H

#include "../inc/allocated_address.h"
#include "../inc/hardware_address.h"
#include "../inc/client_special_id.h"
#include "../inc/addresses_pool.h"
#include <stdio.h>
#include <stdint.h>
#include <list>
#include <unordered_set>

class StateDeserializer {
	public:
		StateDeserializer(const char* filePath);
		~StateDeserializer();

		static bool cacheExists(const char* filePath);

		size_t deserialize(AllocatedAddress* allocatedAddress);
		size_t deserialize(HardwareAddress* hardwareAddress);
		size_t deserialize(ClientSpecialId*);
		size_t deserialize(uint32_t*);
		size_t deserialize(time_t*);
		size_t deserialize(std::list<uint32_t>*);
		size_t deserialize(std::unordered_set<uint32_t>*);
		size_t deserialize(AddressesPool*);
	private:
		FILE* file;		
};

#endif
