#include "../inc/packer.h"
#include <string.h>

using namespace std;

Packer::Packer(uint8_t* buffer) {
	this->buffer = buffer;
}

Packer& Packer::pack(uint8_t optionType, uint32_t value) {
	*(buffer++) = optionType;
	*(buffer++) = sizeof(value);
	*(buffer++) = value;

	return *this;
}

Packer& Packer::pack(uint8_t optionType, uint8_t value) {
	*(buffer++) = optionType;
	*(buffer++) = sizeof(value);
	*(buffer++) = value;

	return *this;
}

Packer& Packer::pack(uint8_t optionType, const std::list<uint32_t>* value) {
	if(!value->empty()) {
		*(buffer++) = optionType;
		*(buffer++) = value->size() * sizeof(uint32_t);

		for(list<uint32_t>::const_iterator it = value->begin(); it != value->end(); it++) {
			uint32_t element = *it;
			memcpy(buffer, &element, sizeof(element));
			buffer += sizeof(element);
		}
	}

	return *this;
}

Packer& Packer::pack(uint8_t optionType) {
	*(buffer++) = optionType;

	return *this;
}
