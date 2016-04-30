#include "../inc/request_handler.h"

RequestHandler::RequestHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator, Server& serv)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator), server(serv) {}


void RequestHandler::handle(struct DHCPMessage& request, Options& options) {
	if(*options.get(SERVER_IDENTIFIER).value == server.serverIp) {
		allocator.freeClientAddress(client);
		// Remove transaction here
	}
}
