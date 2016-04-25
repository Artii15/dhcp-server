#include "inc/server.h"
#include "inc/config.h"
#include "inc/addresses_pool.h"

#include "inc/pool_descriptor.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

int main(int argc, char** argv) {
	using boost::property_tree::ptree;
	ptree config;
	read_json("config.json", config);
	
	PoolDescriptor poolDescriptor;
	BOOST_FOREACH(ptree::value_type &pool, config.get_child("addressesPools")) {
		//poolDescriptor.startAddress = pool.
	}

/*
struct PoolDescriptor {
	uint32_t startAddress;
	uint32_t endAddress;
	uint32_t networkMask;
	uint32_t leaseTime;
	uint32_t dnsAddress;
	uint32_t routerAddress;
};
*/

	return 0;
}
