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

	interface = config.get<std::string>("interface");
	networkAddress = extractAddress(config, "networkAddress");
	networkMask = extractAddress(config, "networkMask");
	
	BOOST_FOREACH(ptree::value_type &poolNode, config.get_child("addressesPools")) {
		ptree &pool = poolNode.second;

		PoolDescriptor poolDescriptor;
		poolDescriptor.startAddress = extractAddress(pool, "startAddress");
		poolDescriptor.endAddress = extractAddress(pool, "endAddress");
		poolDescriptor.networkMask = extractAddress(pool, "networkMask");

		extractAddressesList(pool.get_child("routers"), poolDescriptor.routers);
		extractAddressesList(pool.get_child("dnsServers"), poolDescriptor.dnsServers);

		poolDescriptor.leaseTime = pool.get<uint32_t>("leaseTime");

		addressesPools.push_back(poolDescriptor);
	}
}

uint32_t Config::extractAddress(ptree &node, const char* key) {
	std::string addressString = node.get<std::string>(key);

	return addrFromString(addressString);
}

void Config::extractAddressesList(ptree &addresses, std::list<uint32_t>& target) {
	BOOST_FOREACH(ptree::value_type &rawAddress, addresses) {
		std::string addressString = rawAddress.second.data();	
		target.push_back(addrFromString(addressString));
	}
}

uint32_t Config::addrFromString(std::string& addressString) {
	struct in_addr addressBuffer;
	inet_aton(addressString.c_str(), &addressBuffer);

	return ntohl(addressBuffer.s_addr);
}

const char* Config::getInterface() {
	return interface.c_str();;
}

uint32_t Config::getNetworkAddress() {
	return networkAddress;
}

uint32_t Config::getNetworkMask() {
	return networkMask;
}

const std::list<PoolDescriptor>& Config::getPoolsDescriptors() {
	return addressesPools;
}
