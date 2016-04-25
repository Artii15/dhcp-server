#ifndef CONFIG_H
#define CONFIG_H

#include <list>
#include <boost/property_tree/ptree.hpp>
#include "pool_descriptor.h"

class Config {
	public:
		Config(const char* filePath);
		void load(const char* filePath);

		uint32_t getInterface();
		uint32_t getNetworkAddress();
		const std::list<PoolDescriptor>& getPoolsDescriptors();
	
	private:
		uint32_t interface;
		uint32_t networkAddress;
		
		std::list<PoolDescriptor> addressesPools;

		uint32_t extractAddress(boost::property_tree::ptree &node, const char* key);
};

#endif
