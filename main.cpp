#include "inc/server.h"
#include "inc/config.h"
#include "inc/addresses_pool.h"

int main(int argc, char** argv) {
	printf("%d\n", AddressesPool::isValidPoolString("192.168.1.2:192.168.1.254:255.255.255.0:24"));

	return 0;
}
