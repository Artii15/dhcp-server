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

	timer_delete(taskData->timer);
	delete taskData;
}

void TransactionsStorage::storeTransaction(const Transaction& transaction) {
	transactions[transaction.id] = transaction;
	scheduleCleanTask(transaction.id);
}

void TransactionsStorage::scheduleCleanTask(uint32_t transactionId) {
	CleanTaskData* taskData = new CleanTaskData();
	taskData->transactionId = transactionId;
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

	struct itimerspec newValue;
	memset(&newValue, 0, sizeof(newValue));
	newValue.it_value.tv_sec = config.getTransactionStorageTime();

	struct itimerspec oldValue;
	memset(&oldValue, 0, sizeof(oldValue));

	if(timer_settime(taskData->timer, 0, &newValue, &oldValue) < 0) {
		throw runtime_error("Could not set timer for transaction delete task");
	}
}

const Transaction& TransactionsStorage::getTransaction(uint32_t id) {
	return transactions[id];
}

void TransactionsStorage::removeTransaction(uint32_t id) {
	transactions.erase(id);
}

bool TransactionsStorage::transactionExists(uint32_t id) {
	return transactions.find(id) != transactions.end();
}
