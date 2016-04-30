#include "../inc/inform_handler.h"

InformHandler::InformHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator, Server& serv)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator), server(serv) {}


void InformHandler::handle(struct DHCPMessage&, Options&, uint32_t dstAddr) {
}
