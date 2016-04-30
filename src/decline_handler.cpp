#include "../inc/decline_handler.h"

DeclineHandler::DeclineHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator, Server& serv)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator), server(serv) {}


void DeclineHandler::handle(struct DHCPMessage&, Options&, uint32_t dstAddr) {
	allocator.freeClientAddressButLeaveUnavailable(client);
}
