#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stdint.h>
#include "allocated_address.h"

class Transaction {
	public:
		Transaction();
		Transaction(const Transaction& copy);
		Transaction(uint32_t id, const AllocatedAddress& allocatedAddress);

		uint32_t id;
		AllocatedAddress allocatedAddress;
};

#endif
