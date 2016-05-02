#ifndef PACKER_H
#define PACKER_H

#include <stdint.h>
#include <list>

class Packer {
	public:
		Packer(uint8_t* buffer);

		Packer& pack(uint8_t optionType, uint32_t value);
		Packer& pack(uint8_t optionType, uint8_t value);
		Packer& pack(uint8_t optionType, const std::list<uint32_t>& value);
		Packer& pack(uint8_t optionType);

	private:
		uint8_t* buffer;
};

#endif
