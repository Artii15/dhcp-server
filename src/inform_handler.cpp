#include "../inc/inform_handler.h"
#include "../inc/packer.h"

InformHandler::InformHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator, Server& serv)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator), server(serv) {}


void InformHandler::handle(struct DHCPMessage& message, Options& options, uint32_t dstAddr) {
	if(allocator.hasClientAllocatedAddress(client)) {
		DHCPMessage ack;
		memset(&ack, 0, sizeof(ack));

		ack.op = BOOTREPLY;
		ack.htype = message.htype;
		ack.hlen = message.hlen;
		ack.xid = message.xid;
		ack.yiaddr = 0;
		ack.flags = message.flags;
		ack.giaddr = message.giaddr;
		memcpy(ack.chaddr, message.chaddr, MAX_HADDR_SIZE);
		ack.magicCookie = message.magicCookie;

		const AllocatedAddress& allocatedAddress = allocator.getAllocatedAddress(client);

		Packer packer(ack.options);
		packer.pack(DHCP_MESSAGE_TYPE, (uint8_t)DHCPACK)
			.pack(SERVER_IDENTIFIER, server.serverIp)
			.pack(SUBNET_MASK, allocatedAddress.mask)
			.pack(ROUTERS, allocatedAddress.routers)
			.pack(DNS_OPTION, allocatedAddress.dnsServers)
			.pack(END_OPTION);
		
		server.sender->send(ack, options, DHCPACK);
	}
}
