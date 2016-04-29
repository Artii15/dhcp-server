#include "../inc/discover_handler.h"

DiscoverHandler::DiscoverHandler(TransactionsStorage& storage, Client& clientToHandle, AddressesAllocator& addrAllocator)
	: transactionsStorage(storage), client(clientToHandle), allocator(addrAllocator) {}

void DiscoverHandler::handle(struct DHCPMessage& message, Options& options) {
	if(!transactionsStorage.transactionExists(message.xid)) {
		AllocatedAddress& address = allocator.allocateAddressFor(client);

		transactionsStorage.createTransaction(message.xid, &address);
		sendOffer(message, address);
	}
}

void DiscoverHandler::sendOffer(DHCPMessage& request, AllocatedAddress& allocatedAddress) {
/*
	DHCPMessage offer;
	memset(&offer, 0, sizeof(offer));

	offer.op = BOOTREPLY;
	offer.htype = request->htype;
	offer.hlen = request->hlen;
	offer.xid = request->xid;
	offer.yiaddr = htonl(allocatedAddress.ipAddress);
	offer.flags = request->flags;
	offer.giaddr = request->giaddr;
	memcpy(offer.chaddr, request->chaddr, MAX_HADDR_SIZE);
	offer.magicCookie = request->magicCookie;

	uint8_t* optionsPtr = packIpAddressLeaseTime(offer.options, allocatedAddress.leaseTime);
	optionsPtr = packMessageType(optionsPtr, DHCPOFFER);
	optionsPtr = packServerIdentifier(optionsPtr);
	optionsPtr = packNetworkMask(optionsPtr, allocatedAddress.mask);
	optionsPtr = packRouters(optionsPtr, allocatedAddress.routers);
	optionsPtr = packDnsServers(optionsPtr, allocatedAddress.dnsServers);
	*(optionsPtr++) = END_OPTION;

	libnet_build_udp(Protocol::getServicePortByName("bootps", "udp"), Protocol::getServicePortByName("bootpc", "udp"), LIBNET_UDP_H + sizeof(offer), 0, (uint8_t*)&offer, sizeof(offer), lnetHandle, 0);

	bool performBroadcast = (dhcpMsg->flags & BROADCAST_FLAG);
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
