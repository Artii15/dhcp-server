#include "inc/server.h"

int main(int argc, char** argv) {
	Server server((argc > 1) ? argv[1] : NULL);

	server.listen();

	return 0;
}
