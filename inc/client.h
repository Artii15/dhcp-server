#ifndef CLIENT_H
#define CLIENT_H

#include "hardware_address.h"
#include "client_special_id.h"

enum IdentificationMethod { BASED_ON_HARDWARE, BASED_ON_SPECIAL_ID };
struct Client {
	HardwareAddress hardwareAddress;
	ClientSpecialId specialId;

	IdentificationMethod identificationMethod;
};

#endif
