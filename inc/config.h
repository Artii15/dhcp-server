#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <list>
#include "pool_descriptor.h"

class Config {
	public:
		Config(const char* filePath);
		void load(const char* filePath);
	
	private:
		uint32_t interface;
		uint32_t networkAddress;
		uint32_t networkMask;
		
		std::list<PoolDescriptor> addressesPool;
};

#endif
