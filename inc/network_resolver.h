#ifndef NETWORK_RESOLVER_H
#define NETWORK_RESOLVER_H

#include "config.h"

class NetworkResolver {
	public:
		NetworkResolver(Config&);
		uint32_t determineNetworkAddress(uint32_t giaddr);

	private:
		Config& config;

		uint32_t findNetworkAddressInDescriptors(uint32_t giaddr);
};

#endif
