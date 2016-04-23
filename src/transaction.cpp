#include "../inc/transaction.h"

Transaction::Transaction() {
	id = 0;
	allocatedIpAddress = 0;
	networkMask = 0;
	leaseTime = 0;
}

Transaction::Transaction(const Transaction& copy) {
	id = copy.id;
	allocatedIpAddress = copy.allocatedIpAddress;
	networkMask = copy.networkMask;
	leaseTime = copy.leaseTime;
}

Transaction::Transaction(uint32_t id, uint32_t allocatedIpAddress, uint32_t networkMask, uint32_t leaseTime) {
	this->id = id;
	this->allocatedIpAddress = allocatedIpAddress;
	this->networkMask = networkMask;
	this->leaseTime = leaseTime;
}
