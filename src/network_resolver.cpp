#include "../inc/network_resolver.h"

#include "../inc/unknown_network_exception.h"

NetworkResolver::NetworkResolver(Config& conf): config(conf) {}

uint32_t NetworkResolver::determineNetworkAddress(uint32_t chaddr) {
	return !chaddr ? config.getNetworkAddress() : findNetworkAddressInDescriptors(chaddr);
}

uint32_t NetworkResolver::findNetworkAddressInDescriptors(uint32_t chaddr) {
	const std::list<PoolDescriptor>& poolsDescriptors = config.getPoolsDescriptors();
	std::list<PoolDescriptor>::const_iterator descriptorsIterator = poolsDescriptors.begin();

	for(; descriptorsIterator != poolsDescriptors.end(); descriptorsIterator++) {
		const PoolDescriptor& descriptor = *descriptorsIterator;
		if((chaddr & descriptor.networkMask) == (descriptor.startAddress & descriptor.networkMask))	{
			return chaddr & descriptor.networkMask;
		}
	}

	throw UnknownNetworkException("Searched network could not be found");
}
