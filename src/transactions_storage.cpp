#include "../inc/transactions_storage.h"
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdexcept>

using namespace std;

TransactionsStorage::TransactionsStorage(Config& configuration): config(configuration) {}

void TransactionsStorage::storeTransaction(const Transaction& transaction) {
	transactions[transaction.id] = transaction;

	timer_t timer;
	struct sigevent onTick;
	memset(&onTick, 0, sizeof(onTick));
	onTick.sigev_notify = SIGEV_THREAD;
	onTick.sigev_signo = 0;
	onTick.sigev_value.sival_int = transaction.id;
	onTick.sigev_notify_function = NULL;

	if(timer_create(CLOCK_MONOTONIC, &onTick, &timer) < 0) {
		throw runtime_error("Could not create clock for transaction delete task");
	}
}

const Transaction& TransactionsStorage::getTransaction(uint32_t id) {
	return transactions[id];
}

void TransactionsStorage::removeTransaction(uint32_t id) {
	transactions.erase(id);
}
