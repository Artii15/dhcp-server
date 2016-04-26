#include "../inc/transactions_storage.h"
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdexcept>

using namespace std;

struct CleanTaskData {
	uint32_t transactionId;
	unordered_map<uint32_t, Transaction>* transactions;
	timer_t timer;
};

TransactionsStorage::TransactionsStorage(Config& configuration): config(configuration) {}

void deleteOldTransaction(union sigval data) {
	CleanTaskData* taskData = (CleanTaskData*)data.sival_ptr;
	taskData->transactions->erase(taskData->transactionId);
	
	delete taskData;
}

void TransactionsStorage::storeTransaction(const Transaction& transaction) {
	transactions[transaction.id] = transaction;

	CleanTaskData* taskData = new CleanTaskData();
	taskData->transactionId = transaction.id;
	taskData->transactions = &transactions;

	struct sigevent onTick;
	memset(&onTick, 0, sizeof(onTick));
	onTick.sigev_notify = SIGEV_THREAD;
	onTick.sigev_signo = 0;

	onTick.sigev_value.sival_ptr = taskData;
	onTick.sigev_notify_function = deleteOldTransaction;

	if(timer_create(CLOCK_MONOTONIC, &onTick, &taskData->timer) < 0) {
		throw runtime_error("Could not create clock for transaction delete task");
	}
}

const Transaction& TransactionsStorage::getTransaction(uint32_t id) {
	return transactions[id];
}

void TransactionsStorage::removeTransaction(uint32_t id) {
	transactions.erase(id);
}
