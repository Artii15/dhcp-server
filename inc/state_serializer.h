#ifndef STATE_SERIALIZER_H
#define STATE_SERIALIZER_H

#include "../inc/allocated_address.h"
#include "../inc/hardware_address.h"
#include "../inc/client_special_id.h"
#include "../inc/addresses_pool.h"
#include <stdio.h>
#include <stdint.h>
#include <list>
#include <unordered_set>

class StateSerializer {
	public:
		StateSerializer(const char* filePath);
		~StateSerializer();

		void serialize(const AllocatedAddress& allocatedAddress);
		void serialize(const HardwareAddress& hardwareAddress);
		void serialize(const ClientSpecialId&);
		void serialize(const uint32_t);
		void serializeTime(const time_t); // Needs to have different name, some compilers would not distinguish between time_t and uint32_t
		void serialize(const std::list<uint32_t>&);
		void serialize(const std::unordered_set<uint32_t>&);
		void serialize(const AddressesPool&);
	private:
		FILE* file;		
};

#endif
