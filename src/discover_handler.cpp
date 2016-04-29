#include "../inc/discover_handler.h"

DiscoverHandler::DiscoverHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator) {}

void DiscoverHandler::handle(struct DHCPMessage& message, Options& options) {
	if(!transactionsStorage.transactionExists(message.xid)) {
		allocator.hasClientAllocatedAddress(client) ? assignPreviouslyAssignedAddress() : assignFreshAddress();
	}
}

void DiscoverHandler::assignPreviouslyAssignedAddress() {
	AllocatedAddress address = allocator.allocateNewAddress(client);
}

void DiscoverHandler::assignFreshAddress() {

}