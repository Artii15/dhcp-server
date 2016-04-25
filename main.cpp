#include "inc/config.h"
#include "inc/addresses_allocator.h"

int main(int argc, char** argv) {
	Config config("config.json");
	AddressesAllocator allocator(config);
	

	return 0;
}
