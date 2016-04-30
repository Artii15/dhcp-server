#include "../inc/transactions_storage.h"
#include <string.h>
#include <stdexcept>

using namespace std;

TransactionsStorage::TransactionsStorage(Config& configuration): config(configuration) {}

void deleteOldTransaction(union sigval data) {
	CleanTaskData* taskData = (CleanTaskData*)data.sival_ptr;
	taskData->storage->removeTransaction(taskData->transactionId);
}

Transaction& TransactionsStorage::createTransaction(uint32_t xid, AllocatedAddress* allocatedAddress) {
	Transaction& transaction = transactions[xid];
	transaction.id = xid;
	transaction.allocatedAddress = allocatedAddress;
	scheduleCleanTask(transaction.id);

	return transaction;
}

void TransactionsStorage::scheduleCleanTask(uint32_t transactionId) {
	CleanTaskData& taskData = cleanTasksData[transactionId];
	taskData.transactionId = transactionId;
	taskData.storage = this;

	struct sigevent onTick;
	memset(&onTick, 0, sizeof(onTick));
	onTick.sigev_notify = SIGEV_THREAD;
	onTick.sigev_signo = 0;
	onTick.sigev_value.sival_ptr = &taskData;
	onTick.sigev_notify_function = deleteOldTransaction;

	if(timer_create(CLOCK_MONOTONIC, &onTick, &taskData.timer) < 0) {
		throw runtime_error("Could not create clock for transaction delete task");
	}

	struct itimerspec newValue;
	memset(&newValue, 0, sizeof(newValue));
	newValue.it_value.tv_sec = config.getTransactionStorageTime();

	struct itimerspec oldValue;
	memset(&oldValue, 0, sizeof(oldValue));

	if(timer_settime(taskData.timer, 0, &newValue, &oldValue) < 0) {
		throw runtime_error("Could not set timer for transaction delete task");
	}
}

const Transaction& TransactionsStorage::getTransaction(uint32_t id) {
	return transactions[id];
}

void TransactionsStorage::removeTransaction(uint32_t id) {
	if(transactionExists(id)) {
		transactions.erase(id);
		timer_delete(cleanTasksData[id].timer);
		cleanTasksData.erase(id);
	}
}

bool TransactionsStorage::transactionExists(uint32_t id) {
	return transactions.find(id) != transactions.end();
}
