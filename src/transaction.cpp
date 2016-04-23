#include "../inc/transaction.h"

Transaction::Transaction() {
	id = 0;
	allocatedIpAddress = 0;
}

Transaction::Transaction(const Transaction& copy) {
	id = copy.id;
	allocatedIpAddress = copy.allocatedIpAddress;
}

Transaction::Transaction(uint32_t id, uint32_t allocatedIpAddress) {
	this->id = id;
	this->allocatedIpAddress = allocatedIpAddress;
}
