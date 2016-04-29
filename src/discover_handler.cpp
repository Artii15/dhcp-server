#include "../inc/discover_handler.h"
#include "../inc/packer.h"

DiscoverHandler::DiscoverHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator, Server& serv)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator), server(serv) {}

void DiscoverHandler::handle(struct DHCPMessage& message, Options& options) {
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
}

void DiscoverHandler::sendOffer(DHCPMessage& offer, DHCPMessage& request) {
	uint32_t targetIpAddress;
	uint8_t* targetHardwareAddress[6] = {0};
	if(request.giaddr != 0) {
		targetIpAddress = request.giaddr;
	}
	else if(request.giaddr == 0 && request.ciaddr != 0) {
		targetIpAddress = request.ciaddr;
	}
	else if(request.flags & BROADCAST_FLAG) {
		targetIpAddress = 0xffffffff;
	}
	else {
		targetIpAddress = offer.yiaddr;
		memcpy(targetHardwareAddress, request.chaddr, 6);
	}

/*
	libnet_build_udp(Protocol::getServicePortByName("bootps", "udp"), Protocol::getServicePortByName("bootpc", "udp"), LIBNET_UDP_H + sizeof(offer), 0, (uint8_t*)&offer, sizeof(offer), lnetHandle, 0);


	libnet_autobuild_ipv4(LIBNET_IPV4_H + LIBNET_UDP_H + sizeof(offer), IPPROTO_UDP, performBroadcast ? 0xffffffffffffffff : offer.yiaddr, lnetHandle);

	uint8_t dstEthAddr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	if(!performBroadcast) {
		memcpy(dstEthAddr, dhcpMsg->chaddr, 6);
	}
	libnet_autobuild_ethernet(dstEthAddr, ETH_P_IP, lnetHandle);

	libnet_write(lnetHandle);
	libnet_clear_packet(lnetHandle);
*/
}
