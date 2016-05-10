#ifndef CLIENT_SPECIAL_ID
#define CLIENT_SPECIAL_ID

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "bytes_comparator.h"

#define CLIENT_SPECIAL_ID_MAX_LEN 255

struct ClientSpecialId {
	uint8_t type;
	uint8_t value[CLIENT_SPECIAL_ID_MAX_LEN];

	inline bool operator < (const ClientSpecialId &id) const {
        return (type < id.type) || ((type == id.type) && BytesComparator::compareArrays(value, id.value, CLIENT_SPECIAL_ID_MAX_LEN));
    }
};

#endif
