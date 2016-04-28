#ifndef CLIENT_H
#define CLIENT_H

#include "hardware_address.h"
#include "client_special_id.h"

struct Client {
	union id {
		HardwareAddress hardwareAddress;	
		ClientSpecialId specialId;
	};
};

#endif
