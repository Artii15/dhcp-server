#ifndef OPTION_H
#define OPTION_H

#include <stdint.h>

struct Option {
	uint8_t code;
	uint8_t length;
	uint8_t* value;
};

#endif
