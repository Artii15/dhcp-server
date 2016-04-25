#include "../inc/config.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

Config::Config(const char* filePath) {
	load(filePath);
}

void Config::load(const char* filePath) {
/*
	using boost::property_tree::ptree;
	ptree config;
	read_json("config.json", config);
	
	PoolDescriptor poolDescriptor;
	BOOST_FOREACH(ptree::value_type &pool, config.get_child("addressesPools")) {
		std::string address = pool.second.get<std::string>("startAddress");
		poolDescriptor.startAddress = atol(address.c_str());
	}

	printf("%u\n", poolDescriptor.startAddress);

struct PoolDescriptor {
	uint32_t startAddress;
	uint32_t endAddress;
	uint32_t networkMask;
	uint32_t leaseTime;
	uint32_t dnsAddress;
	uint32_t routerAddress;
};
*/

}
