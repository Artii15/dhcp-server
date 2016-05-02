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

	static Config config("config.json");
	static TransactionsStorage storage(config);
	static AddressesAllocator allocator(config);
	static Server server(config, allocator, storage);

	server.listen();

	return 0;
}
