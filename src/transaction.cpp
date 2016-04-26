#include "../inc/transaction.h"

Transaction::Transaction() {}

Transaction::Transaction(const Transaction& copy): Transaction(copy.id, copy.allocatedAddress) {}

Transaction::Transaction(uint32_t id, const AllocatedAddress& address): allocatedAddress(address) {
	this->id = id;
}
