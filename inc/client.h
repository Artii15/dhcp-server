#ifndef CLIENT_H
#define CLIENT_H

#include "hardware_address.h"
#include "client_special_id.h"

enum ClientIdType { ID_BASED_ON_HARDWARE, SPECIAL_ID };
struct Client {
	union id {
		HardwareAddress* hardwareAddress;	
		ClientSpecialId* specialId;
	} id;

	ClientIdType idType;	
};

#endif
