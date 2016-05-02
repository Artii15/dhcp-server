#ifndef STATE_SERIALIZER_H
#define STATE_SERIALIZER_H

#include "../inc/allocated_address.h"
#include "../inc/hardware_address.h"
#include <stdio.h>

class StateSerializer {
	public:
		StateSerializer(const char* filePath);
		~StateSerializer();

		void serialize(const AllocatedAddress& allocatedAddress);
		void serialize(const HardwareAddress& hardwareAddress);
		void serialize(const unsigned);
	private:
		FILE* file;		
};

#endif
