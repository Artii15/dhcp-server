#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

class Config {
	public:
		Config(const char* filePath);
		const std::string& get(const std::string &key);
	
	private:
		void parse(const char* filePath);
		std::map<std::string, std::string> settings;
};

#endif
