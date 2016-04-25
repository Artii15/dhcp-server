#include "../inc/config.h"


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <strings.h>

using boost::property_tree::ptree;

Config::Config(const char* filePath) {
	load(filePath);
}

void Config::load(const char* filePath) {

	ptree config;
	read_json(filePath, config);
	
	BOOST_FOREACH(ptree::value_type &pool, config.get_child("addressesPools")) {
		PoolDescriptor poolDescriptor;

		poolDescriptor.startAddress = extractAddress(pool, "startAddress");
		poolDescriptor.endAddress = extractAddress(pool, "endAddress");
		poolDescriptor.networkMask = extractAddress(pool, "networkMask");
		poolDescriptor.dnsAddress = extractAddress(pool, "dnsAddress");
		poolDescriptor.routerAddress = extractAddress(pool, "routerAddress");

		poolDescriptor.leaseTime = pool.second.get<uint32_t>("leaseTime");

		addressesPools.push_back(poolDescriptor);
	}
}

uint32_t Config::extractAddress(ptree::value_type &pool, const char* key) {
	std::string rawDataBuffer = pool.second.get<std::string>(key);
	struct in_addr addressBuffer;
	inet_aton(rawDataBuffer.c_str(), &addressBuffer);

	return ntohl(addressBuffer.s_addr);
}
