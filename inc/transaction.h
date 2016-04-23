#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stdint.h>

class Transaction {
	public:
		Transaction();
		Transaction(const Transaction& copy);
		Transaction(uint32_t id, uint32_t allocatedIpAddress, uint32_t leaseTime);

		uint32_t id;
		uint32_t allocatedIpAddress;
		uint32_t leaseTime;
};

#endif
