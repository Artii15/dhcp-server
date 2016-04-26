#ifndef CONFIG_H
#define CONFIG_H

#include <list>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include "pool_descriptor.h"

class Config {
	public:
		Config(const char* filePath);
		void load(const char* filePath);

		const char* getInterface();
		uint32_t getNetworkAddress();
		uint32_t getNetworkMask();
		uint32_t getTransactionStorageTime();
		const std::list<PoolDescriptor>& getPoolsDescriptors();
	
	private:
		std::string interface;
		uint32_t networkAddress;
		uint32_t networkMask;
		uint32_t transactionStorageTime;
		
		std::list<PoolDescriptor> addressesPools;

		uint32_t addrFromString(std::string& addressString);
		uint32_t extractAddress(boost::property_tree::ptree &node, const char* key);
		void extractAddressesList(boost::property_tree::ptree &addresses, std::list<uint32_t>& target);
};

#endif
