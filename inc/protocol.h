#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

class Protocol {
	public:
		static uint16_t getServicePortByName(const char* serviceName, const char* protocolName);
};

#endif
