#ifndef DISCOVER_HANDLER_H
#define DISCOVER_HANDLER_H

#include "dhcp_message.h"
#include "options.h"
#include "transactions_storage.h"
#include "client.h"
#include "addresses_allocator.h"
#include "server.h"

class DiscoverHandler {
	public:
		DiscoverHandler(TransactionsStorage&, Client&, AddressesAllocator&, Server&);
		void handle(struct DHCPMessage&, Options&);

	private:
		TransactionsStorage& transactionsStorage;
		Client& client;
		AddressesAllocator& allocator;
		Server& server;

		void sendOffer(DHCPMessage& request, AllocatedAddress& allocatedAddress);
		void sendOffer(DHCPMessage& offer, DHCPMessage& request);
};

#endif
