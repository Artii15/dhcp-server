#ifndef SENDER_H
#define SENDER_H

#include <libnet.h>
#include "dhcp_message.h"
#include "allocated_address.h"

class Sender {
	public:
		Sender(libnet_t* lnetHandle);
		void send(DHCPMessage&, const AllocatedAddress&, unsigned messageType);

	private:
		libnet_t* lnetHandle;
		void fillBroadcastAddress(uint8_t* buffer);
};

#endif
