#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class Config {
	public:
		Config(const char* filePath);
		const std::string& get(const std::string &key);
	
	private:
		void parse(const char* filePath);
		std::unordered_map<std::string, std::string> settings;
};

#endif
