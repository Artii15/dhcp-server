#include "../inc/packet_converter.h"
#include <arpa/inet.h>

void PacketConverter::toHostReprezentation(DHCPMessage& message) {
	message.xid = ntohl(message.xid);
	message.secs = ntohs(message.secs);
	message.flags = ntohs(message.flags);
	message.ciaddr = ntohl(message.ciaddr);
	message.yiaddr = ntohl(message.yiaddr);
	message.siaddr = ntohl(message.siaddr);
	message.giaddr = ntohl(message.giaddr);
}

void PacketConverter::toNetworkReprezentation(DHCPMessage& message) {
	message.xid = htonl(message.xid);
	message.secs = htons(message.secs);
	message.flags = htons(message.flags);
	message.ciaddr = htonl(message.ciaddr);
	message.yiaddr = htonl(message.yiaddr);
	message.siaddr = htonl(message.siaddr);
	message.giaddr = htonl(message.giaddr);
}
