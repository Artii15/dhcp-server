#include "../inc/network_resolver.h"

#include "../inc/unknown_network_exception.h"

NetworkResolver::NetworkResolver(Config& conf): config(conf) {}

uint32_t NetworkResolver::determineNetworkAddress(uint32_t giaddr) {
	return !giaddr ? config.getNetworkAddress() : findNetworkAddressInDescriptors(giaddr);
}

uint32_t NetworkResolver::findNetworkAddressInDescriptors(uint32_t giaddr) {
	const std::list<PoolDescriptor>& poolsDescriptors = config.getPoolsDescriptors();
	std::list<PoolDescriptor>::const_iterator descriptorsIterator = poolsDescriptors.begin();

	for(; descriptorsIterator != poolsDescriptors.end(); descriptorsIterator++) {
		const PoolDescriptor& descriptor = *descriptorsIterator;
		if((giaddr & descriptor.networkMask) == (descriptor.startAddress & descriptor.networkMask))	{
			return giaddr & descriptor.networkMask;
		}
	}

	throw UnknownNetworkException("Searched network could not be found");
}
