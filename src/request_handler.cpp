#include "../inc/request_handler.h"

RequestHandler::RequestHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator, Server& serv)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator), server(serv) {}
