#include "../inc/config.h"
#include "../inc/addresses_allocator.h"
#include "../inc/server.h"
#include "../inc/transactions_storage.h"

#include <signal.h>
#include <stdlib.h>

void finish(int signum) {
	exit(EXIT_SUCCESS);
}

int main(int argc, char** argv) {
	signal(SIGINT, finish);

	Config config("config.json");
	TransactionsStorage storage(config);
	AddressesAllocator allocator(config);
	static Server server(config, allocator, storage);

	server.listen();

	return 0;
}
