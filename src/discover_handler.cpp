#include "../inc/discover_handler.h"
#include "../inc/packer.h"
#include "../inc/protocol.h"

DiscoverHandler::DiscoverHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator, Server& serv)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator), server(serv) {}

void DiscoverHandler::handle(struct DHCPMessage& message, Options& options, uint32_t dstAddr) {
	if(!transactionsStorage.transactionExists(message.xid)) {
		AllocatedAddress& address = allocator.allocateAddressFor(client);

		transactionsStorage.createTransaction(message.xid, &address);
		sendOffer(message, address);
	}
}

void DiscoverHandler::sendOffer(DHCPMessage& request, AllocatedAddress& allocatedAddress) {
	DHCPMessage offer;
	memset(&offer, 0, sizeof(offer));

	offer.op = BOOTREPLY;
	offer.htype = request.htype;
	offer.hlen = request.hlen;
	offer.xid = request.xid;
	offer.yiaddr = allocatedAddress.ipAddress;
	offer.flags = request.flags;
	offer.giaddr = request.giaddr;
	memcpy(offer.chaddr, request.chaddr, MAX_HADDR_SIZE);
	offer.magicCookie = request.magicCookie;

	Packer packer(offer.options);
	packer.pack(IP_ADDRESS_LEASE_TIME, allocatedAddress.leaseTime)
		.pack(DHCP_MESSAGE_TYPE, (uint8_t)DHCPOFFER)
		.pack(SERVER_IDENTIFIER, server.serverIp)
		.pack(SUBNET_MASK, allocatedAddress.mask)
		.pack(ROUTERS, allocatedAddress.routers)
		.pack(DNS_OPTION, allocatedAddress.dnsServers)
		.pack(END_OPTION);
	
	server.sender->send(offer, DHCPOFFER);
}
