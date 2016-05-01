#ifndef SENDER_H
#define SENDER_H

#include <libnet.h>
#include "dhcp_message.h"
#include "allocated_address.h"
#include "options.h"

#define IP_BROADCAST_ADDR 0xffffffff

class Sender {
	public:
		Sender(libnet_t* lnetHandle);
		void send(DHCPMessage&, unsigned messageType);

	private:
		libnet_t* lnetHandle;
		void fillBroadcastAddress(uint8_t* buffer);
};

#endif
