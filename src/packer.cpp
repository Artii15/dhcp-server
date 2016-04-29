#include "../inc/packer.h"
#include <string.h>

using namespace std;

uint8_t* Packer::pack(uint8_t* dst, uint8_t optionType, uint32_t value) {
	*(dst++) = optionType;
	*(dst++) = sizeof(value);
	*(dst++) = value;

	return dst;
}

uint8_t* Packer::pack(uint8_t* dst, uint8_t optionType, uint8_t value) {
	*(dst++) = optionType;
	*(dst++) = sizeof(value);
	*(dst++) = value;

	return dst;
}

uint8_t* Packer::pack(uint8_t* dst, uint8_t optionType, const std::list<uint32_t>* value) {
	if(!value->empty()) {
		*(dst++) = optionType;
		*(dst++) = value->size() * sizeof(uint32_t);

		for(list<uint32_t>::const_iterator it = value->begin(); it != value->end(); it++) {
			uint32_t element = *it;
			memcpy(dst, &element, sizeof(element));
			dst += sizeof(element);
		}
	}

	return dst;
}
