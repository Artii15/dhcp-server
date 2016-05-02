#include "../inc/state_deserializer.h"
#include <stdio.h>

using namespace std;

StateDeserializer::StateDeserializer(const char* filePath) {
	file = fopen(filePath, "rb");
}

StateDeserializer::~StateDeserializer() {
	fclose(file);
}
