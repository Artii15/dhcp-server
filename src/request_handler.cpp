#include "../inc/request_handler.h"
#include "../inc/packer.h"

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
		const AllocatedAddress& allocatedAddress = *transactionsStorage.getTransaction(request.xid).allocatedAddress;
		if(isRequestedAddressValid(request, options, allocatedAddress)) {
			sendAck(request, allocatedAddress);
		}
		else {
			sendNak(request, options);
		}
	}
}

bool RequestHandler::isRequestedAddressValid(DHCPMessage& request, Options& options, const AllocatedAddress& allocatedAddress) {
	return options.exists(REQUESTED_IP_ADDRESS) 
		&& (uint32_t)*options.get(REQUESTED_IP_ADDRESS).value == allocatedAddress.ipAddress;
}

void RequestHandler::sendAck(DHCPMessage& request, const AllocatedAddress& allocatedAddress) {
	DHCPMessage ack;
	memset(&ack, 0, sizeof(ack));

	ack.op = BOOTREPLY;
	ack.htype = request.htype;
	ack.hlen = request.hlen;
	ack.xid = request.xid;
	ack.yiaddr = allocatedAddress.ipAddress;
	ack.flags = request.flags;
	ack.giaddr = request.giaddr;
	memcpy(ack.chaddr, request.chaddr, MAX_HADDR_SIZE);
	ack.magicCookie = request.magicCookie;


	Packer packer(ack.options);
	packer.pack(IP_ADDRESS_LEASE_TIME, allocatedAddress.leaseTime)
		.pack(DHCP_MESSAGE_TYPE, (uint8_t)DHCPOFFER)
		.pack(SERVER_IDENTIFIER, server.serverIp)
		.pack(SUBNET_MASK, allocatedAddress.mask)
		.pack(ROUTERS, allocatedAddress.routers)
		.pack(DNS_OPTION, allocatedAddress.dnsServers)
		.pack(END_OPTION);
	
	/*

	libnet_build_udp(Protocol::getServicePortByName("bootps", "udp"), Protocol::getServicePortByName("bootpc", "udp"), LIBNET_UDP_H + sizeof(ack), 0, (uint8_t*)&ack, sizeof(ack), server.lnetHandle, 0);

	libnet_autobuild_ipv4(LIBNET_IPV4_H + LIBNET_UDP_H + sizeof(ack), IPPROTO_UDP, targetIpAddress, server.lnetHandle);

	uint8_t zeroAddr[6] = {0};
	if(memcmp(zeroAddr, targetHardwareAddress, 6) != 0) {
		libnet_autobuild_ethernet(targetHardwareAddress, ETH_P_IP, server.lnetHandle);
	}

	libnet_write(server.lnetHandle);
	libnet_clear_packet(server.lnetHandle);
	*/
}

void RequestHandler::sendNak(DHCPMessage&, Options&) {

}
