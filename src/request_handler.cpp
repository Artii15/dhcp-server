#include "../inc/request_handler.h"

RequestHandler::RequestHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator, Server& serv)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator), server(serv) {}


void RequestHandler::handle(struct DHCPMessage& request, Options& options) {
	ClientState clientState = determineClientState(request, options);

	switch(clientState) {
		case SELECTING:
			handleSelectingState(request, options);
			break;
		case INIT_REBOOT:
			break;
		case RENEWING:
			break;
		case REBINDING:
			break;
		case UNKNOWN:
			break;
	}
	transactionsStorage.removeTransaction(request.xid);
}

ClientState RequestHandler::determineClientState(struct DHCPMessage& request, Options& options) {
	if(options.exists(SERVER_IDENTIFIER) && request.ciaddr == 0 && request.yiaddr != 0) {
		return SELECTING;
	}
	else if((!options.exists(SERVER_IDENTIFIER) || (uint32_t)*options.get(SERVER_IDENTIFIER).value == 0)
			&& request.yiaddr != 0 && request.ciaddr == 0) {
		return INIT_REBOOT;
	}
	else if((!options.exists(SERVER_IDENTIFIER) || (uint32_t)*options.get(SERVER_IDENTIFIER).value) 
			&& request.yiaddr == 0 && request.ciaddr != 0) {
		return RENEWING;
	}
	else if((!options.exists(SERVER_IDENTIFIER) || (uint32_t)*options.get(SERVER_IDENTIFIER).value) 
			&& request.ciaddr != 0) {
		return REBINDING;
	}
	else {
		return UNKNOWN;
	}
}

void RequestHandler::handleSelectingState(struct DHCPMessage& request, Options& options) {
	if(*options.get(SERVER_IDENTIFIER).value != server.serverIp) {
		allocator.freeClientAddress(client);
	}
	else if(transactionsStorage.transactionExists(request.xid)) {
		if(isRequestedAddressValid(request, options)) {
			sendAck(request, options);
		}
		else {
			sendNak(request, options);
		}
	}
}

bool RequestHandler::isRequestedAddressValid(DHCPMessage& request, Options& options) {
	return options.exists(REQUESTED_IP_ADDRESS) 
		&& (uint32_t)*options.get(REQUESTED_IP_ADDRESS).value == transactionsStorage.getTransaction(request.xid).allocatedAddress->ipAddress;
}

void RequestHandler::sendAck(DHCPMessage&, Options&) {

}

void RequestHandler::sendNak(DHCPMessage&, Options&) {

}
