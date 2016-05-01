#ifndef PACKET_CONVERTER_H
#define PACKET_CONVERTER_H

#include "dhcp_message.h"

class PacketConverter {
	public:
		static void toHostReprezentation(DHCPMessage&);
		static void toNetworkReprezentation(DHCPMessage&);
};

#endif
