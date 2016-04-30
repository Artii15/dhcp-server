#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "server.h"
#include "client.h"
#include "transactions_storage.h"
#include "addresses_allocator.h"
#include "dhcp_message.h"
#include "options.h"

class RequestHandler {
	public:
		RequestHandler(TransactionsStorage&, Client&, AddressesAllocator&, Server&);
		void handle(struct DHCPMessage&, Options&);

	private:
		TransactionsStorage& transactionsStorage;
		Client& client;
		AddressesAllocator& allocator;
		Server& server;
};

#endif
