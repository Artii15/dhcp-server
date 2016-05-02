#ifndef STATE_SERIALIZER_H
#define STATE_SERIALIZER_H

#include "../inc/allocated_address.h"
#include "../inc/hardware_address.h"
#include <stdio.h>
#include <stdint.h>
#include <list>

class StateSerializer {
	public:
		StateSerializer(const char* filePath);
		~StateSerializer();

		void serialize(const AllocatedAddress& allocatedAddress);
		void serialize(const HardwareAddress& hardwareAddress);
		void serialize(const unsigned);
		void serialize(const std::list<uint32_t>&);
	private:
		FILE* file;		
};

#endif
