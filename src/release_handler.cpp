#include "../inc/release_handler.h"

ReleaseHandler::ReleaseHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator, Server& serv)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator), server(serv) {}


void ReleaseHandler::handle(struct DHCPMessage&, Options&, uint32_t dstAddr) {
}
