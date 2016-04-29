#ifndef DISCOVER_HANDLER_H
#define DISCOVER_HANDLER_H

#include "dhcp_message.h"
#include "options.h"
#include "transactions_storage.h"
#include "client.h"
#include "addresses_allocator.h"

class DiscoverHandler {
	public:
		DiscoverHandler(TransactionsStorage&, Client&, AddressesAllocator&);
		void handle(struct DHCPMessage&, Options&);

	private:
		TransactionsStorage& transactionsStorage;
		Client& client;
		AddressesAllocator& allocator;
};

#endif
