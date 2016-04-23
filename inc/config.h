#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

class Config {
	public:
		Config(const std::string &filePath);
		const std::string& get(const std::string &key);
	
	private:
		void parse(const std::string &filePath)
		std::map<const std::string, const std::string> settings;
};
