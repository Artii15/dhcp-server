#include "../inc/discover_handler.h"

DiscoverHandler::DiscoverHandler(TransactionsStorage& storage): transactionsStorage(storage) {}

void DiscoverHandler::handle(struct DHCPMessage& message, Options& options) {
	if(transactionsStorage.transactionExists(message.xid)) {
		return;
	}

/*
	HardwareAddress clientAddress(dhcpMsg->htype, dhcpMsg->chaddr);
	AllocatedAddress allocatedAddress = addressesAllocator.allocate(clientAddress, ntohl(dhcpMsg->giaddr), ntohl(dhcpMsg->yiaddr));

	transactionsStorage.storeTransaction(Transaction(dhcpMsg->xid, allocatedAddress));
	sendOffer(dhcpMsg, allocatedAddress);
	*/
}
