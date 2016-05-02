#include "../inc/state_deserializer.h"
#include <stdio.h>

using namespace std;

bool StateDeserializer::cacheExists(const char* filePath) {
	FILE *file;
    if((file = fopen(filePath, "r")) != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

StateDeserializer::StateDeserializer(const char* filePath) {
	file = fopen(filePath, "rb");
}

StateDeserializer::~StateDeserializer() {
	fclose(file);
}

void StateDeserializer::deserialize(uint32_t* target) {

}
