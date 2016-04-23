#include "../inc/config.h"

#include <fstream>
#include <sstream>

using namespace std;

Config::Config(const char* filePath) {
	parse(filePath);
}

void Config::parse(const char* filePath) {
	ifstream configFile(filePath);

	string line;
	while(getline(configFile, line)) {
		istringstream lineBuffer(line);
		
		string key;
		if(getline(lineBuffer, key, '=')) {
			string value;
			if(getline(lineBuffer, value)) {
				settings[key] = value;
			}
		}
	}
}

const string& Config::get(const string &key) {
	return settings[key];
}
