#include "inc/server.h"
#include "inc/config.h"

int main(int argc, char** argv) {
	Config config("config");
	Server server(config);

	server.listen();

	return 0;
}
