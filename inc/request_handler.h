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

		void handleSelectingState(DHCPMessage&, Options&);
		bool isRequestedAddressValid(DHCPMessage&, Options&, const AllocatedAddress&);

		void handleInitRebootState(DHCPMessage&, Options&);

		void respond(DHCPMessage&, const AllocatedAddress&, uint8_t messageType);
};

#endif
