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

		void deserialize(const AllocatedAddress& allocatedAddress);
		void deserialize(const HardwareAddress& hardwareAddress);
		void deserialize(const ClientSpecialId&);
		void deserialize(uint32_t*);
		void deserialize(const std::list<uint32_t>&);
		void deserialize(const std::unordered_set<uint32_t>&);
		void deserialize(const AddressesPool&);
	private:
		FILE* file;		
};

#endif
