#include "inc/config.h"
#include "inc/addresses_allocator.h"
#include "inc/server.h"

int main(int argc, char** argv) {
	Config config("config.json");
	AddressesAllocator allocator(config);
	Server server(allocator, config);

	server.listen();

	return 0;
}
