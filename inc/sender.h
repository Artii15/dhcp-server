#ifndef SENDER_H
#define SENDER_H

#include <libnet.h>
#include "dhcp_message.h"
#include "allocated_address.h"

class Sender {
	public:
		Sender(libnet_t* lnetHandle);
		void send(DHCPMessage request, const AllocatedAddress&);

	private:
		libnet_t* lnetHandle;
};

#endif
