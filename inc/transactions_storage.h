#ifndef TRANSACTIONS_STORAGE_H
#define TRANSACTIONS_STORAGE_H

#include "transaction.h"
#include "config.h"
#include <unordered_map>

class TransactionsStorage {
	public:
		TransactionsStorage(Config& config);
		void storeTransaction(const Transaction&);
		const Transaction& getTransaction(uint32_t id);
		void removeTransaction(uint32_t id);

	private:
		Config& config;
		std::unordered_map<uint32_t, Transaction> transactions;
};

#endif
