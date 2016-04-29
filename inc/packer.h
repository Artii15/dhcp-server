#ifndef PACKER_H
#define PACKER_H

#include <stdint.h>
#include <list>

class Packer {
	public:
		uint8_t* pack(uint8_t* dst, uint8_t optionType, uint32_t value);
		uint8_t* pack(uint8_t* dst, uint8_t optionType, uint8_t value);
		uint8_t* pack(uint8_t* dst, uint8_t optionType, const std::list<uint32_t>* value);
};

#endif
