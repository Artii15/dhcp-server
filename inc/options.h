#ifndef OPTIONS_H
#define OPTIONS_H

#include <unordered_map>
#include "option.h"

class Options {
	public:
		Options(uint8_t* rawOptions, unsigned maxOptionsLength);
		Option& get(uint8_t code);
		bool exists(uint8_t code);

	private:
		void read(uint8_t* rawOptions, unsigned maxOptionsLength);
		void tryToSetHostBytesOrder(Option&);
		void toHost32(Option&);
		void toHost32(uint8_t* bytes);
		void toHostArray32(Option&);


		std::unordered_map<uint8_t, Option> options;
};

#endif
