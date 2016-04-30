#ifndef DECLINE_HANDLER_H
#define DECLINE_HANDLER_H

#include "dhcp_message.h"
#include "options.h"
#include "transactions_storage.h"
#include "client.h"
#include "addresses_allocator.h"
#include "server.h"

class DeclineHandler {
	public:
		DeclineHandler(TransactionsStorage&, Client&, AddressesAllocator&, Server&);
		void handle(struct DHCPMessage&, Options&, uint32_t dstAddr);

	private:
		TransactionsStorage& transactionsStorage;
		Client& client;
		AddressesAllocator& allocator;
		Server& server;
};

#endif
