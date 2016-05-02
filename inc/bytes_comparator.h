#ifndef BYTES_COMPARAT_H
#define  BYTES_COMPARAT_H

#include <stdint.h>

class BytesComparator {
	public:
		static int compareArrays(const uint8_t* arr1, const uint8_t* arr2, const uint8_t arraysSize);
};

#endif
