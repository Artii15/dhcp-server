#include "../inc/bytes_comparator.h"

int BytesComparator::compareArrays(const uint8_t* arr1, const uint8_t* arr2, const uint8_t arraysSize) {
	for(unsigned i = 0; i < arraysSize; ++i) {
		if(arr1[i] < arr2[i]) {
			return -1;
		}
		else if(arr1[i] > arr2[i]) {
			return 1;
		}
	}

	return 0;
}
