#include "../inc/discover_handler.h"

DiscoverHandler::DiscoverHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator) {}

void DiscoverHandler::handle(struct DHCPMessage& message, Options& options) {
	if(transactionsStorage.transactionExists(message.xid)) {
		return;
	}

	if(allocator.hasClientAllocatedAddress(client)) {
		assignPreviouslyAssignedAddress();	
	}
	else {
		assignFreshAddress();
	}
}

void DiscoverHandler::assignPreviouslyAssignedAddress() {

}

void DiscoverHandler::assignFreshAddress() {

}
