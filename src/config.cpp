#include "../inc/config.h"


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <strings.h>

Config::Config(const char* filePath) {
	load(filePath);
}

void Config::load(const char* filePath) {
	using boost::property_tree::ptree;

	ptree config;
	read_json(filePath, config);
	
	BOOST_FOREACH(ptree::value_type &pool, config.get_child("addressesPools")) {
		PoolDescriptor poolDescriptor;

		struct in_addr addressBuffer;
		std::string rawDataBuffer = pool.second.get<std::string>("startAddress");
		inet_aton(rawDataBuffer.c_str(), &addressBuffer);
		poolDescriptor.startAddress = ntohl(addressBuffer.s_addr);

		bzero(&addressBuffer, sizeof(addressBuffer));
		rawDataBuffer = pool.second.get<std::string>("endAddress");
		inet_aton(rawDataBuffer.c_str(), &addressBuffer);
		poolDescriptor.endAddress = ntohl(addressBuffer.s_addr);

		bzero(&addressBuffer, sizeof(addressBuffer));
		rawDataBuffer = pool.second.get<std::string>("networkMask");
		inet_aton(rawDataBuffer.c_str(), &addressBuffer);
		poolDescriptor.networkMask = ntohl(addressBuffer.s_addr);

		bzero(&addressBuffer, sizeof(addressBuffer));
		rawDataBuffer = pool.second.get<std::string>("dnsAddress");
		inet_aton(rawDataBuffer.c_str(), &addressBuffer);
		poolDescriptor.dnsAddress = ntohl(addressBuffer.s_addr);

		bzero(&addressBuffer, sizeof(addressBuffer));
		rawDataBuffer = pool.second.get<std::string>("routerAddress");
		inet_aton(rawDataBuffer.c_str(), &addressBuffer);
		poolDescriptor.routerAddress = ntohl(addressBuffer.s_addr);

		poolDescriptor.leaseTime = pool.second.get<uint32_t>("leaseTime");

		addressesPools.push_back(poolDescriptor);
	}
}
