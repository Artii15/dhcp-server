#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "server.h"
#include "client.h"
#include "transactions_storage.h"
#include "addresses_allocator.h"

class RequestHandler {
	public:
		RequestHandler(TransactionsStorage&, Client&, AddressesAllocator&, Server&);

	private:
		TransactionsStorage& transactionsStorage;
		Client& client;
		AddressesAllocator& allocator;
		Server& server;
};

#endif
