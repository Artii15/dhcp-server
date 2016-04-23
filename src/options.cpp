#include "../inc/options.h"
#include <stdio.h>

Options::Options(uint8_t* rawOptions, unsigned maxOptionsLength) {
	read(rawOptions, maxOptionsLength);
}

void Options::read(uint8_t* rawOptions, unsigned maxOptionsLength) {
	for(unsigned i = 0; i < maxOptionsLength - 2;) {
		struct Option option;
		option.code = rawOptions[i];
		option.length = rawOptions[i+1];
		option.value = &rawOptions[i+2];

		if(option.length <= maxOptionsLength - (i + 2)) {
			options[option.code] = option;
		}

		i += (sizeof(option.code) + sizeof(option.length) + option.length);
	}
}


Option& Options::get(uint8_t code) {
	return options[code];
}
