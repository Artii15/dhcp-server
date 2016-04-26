#include "../inc/config.h"
#include "../inc/addresses_allocator.h"
#include "../inc/server.h"
#include "../inc/transactions_storage.h"

int main(int argc, char** argv) {
	Config config("config.json");
	TransactionsStorage storage(config);
	AddressesAllocator allocator(config);
	Server server(config, allocator, storage);

	server.listen();

	return 0;
}
