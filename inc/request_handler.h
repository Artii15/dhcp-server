#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "server.h"
#include "client.h"
#include "transactions_storage.h"
#include "addresses_allocator.h"
#include "dhcp_message.h"
#include "options.h"

enum ClientState { SELECTING, INIT_REBOOT, RENEWING, REBINDING, UNKNOWN };
class RequestHandler {
	public:
		RequestHandler(TransactionsStorage&, Client&, AddressesAllocator&, Server&);
		void handle(struct DHCPMessage&, Options&);

	private:
		TransactionsStorage& transactionsStorage;
		Client& client;
		AddressesAllocator& allocator;
		Server& server;

		ClientState determineClientState(struct DHCPMessage&, Options&);

		void handleSelectingState(struct DHCPMessage&, Options&);
		bool isRequestedAddressValid(Options&);
		void sendAck(DHCPMessage&, Options&);
		void sendNak(DHCPMessage&, Options&);
};

#endif
