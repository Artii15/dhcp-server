#include "../inc/options.h"
#include <string.h>
#include <arpa/inet.h>

using namespace std;

Options::Options(uint8_t* rawOptions) {
	read(rawOptions, calculateOptionsLength(rawOptions));
}

size_t Options::calculateOptionsLength(uint8_t* rawOptions) {
	size_t optionsSize = 0;
	uint8_t* seek = rawOptions;
	bool endReaded = false;

	while(!endReaded) {
		uint8_t optionCode = *(seek++);
		uint8_t optionLength = *(seek++);
		size_t optionSize = sizeof(optionCode) + sizeof(optionLength) + optionLength;

		seek += optionLength;
		optionsSize += optionSize;

		endReaded = (optionCode == END_OPTION);
	}

	return optionsSize;
}

Options::Options(uint8_t* rawOptions, unsigned maxOptionsLength) {
	read(rawOptions, maxOptionsLength);
}

void Options::read(uint8_t* rawOptions, unsigned maxOptionsLength) {
	for(unsigned i = 0; i < maxOptionsLength - 2;) {
		struct Option option;
		option.code = rawOptions[i];
		option.length = rawOptions[i+1];
		option.value = &rawOptions[i+2];

		if(option.length <= maxOptionsLength - (i + 2)) {
			options[option.code] = option;
		}

		if(option.code == END_OPTION) {
			break;
		}

		i += (sizeof(option.code) + sizeof(option.length) + option.length);
	}
}

void Options::toHostReprezentation() {
	for(unordered_map<uint8_t, Option>::iterator it = options.begin(); it != options.end(); it++) {
		Option& option = it->second;
		tryToSetHostBytesOrder(option);
	}
}

void Options::tryToSetHostBytesOrder(Option& option) {
	switch(option.code) {
		case SUBNET_MASK: 
			toHost32(option);
			break;
		case ROUTERS: 
			toHostArray32(option);
			break;
		case DNS_OPTION: 
			toHostArray32(option);
			break;
		case REQUESTED_IP_ADDRESS: 
			toHost32(option);
			break;
		case IP_ADDRESS_LEASE_TIME: 
			toHost32(option);
			break;
		case SERVER_IDENTIFIER: 
			toHost32(option);
			break;
		default:
			break;
	}
}

void Options::toHostArray32(Option& option) {
	for(unsigned i = 0; i < option.length; i += sizeof(uint32_t)) {
		toHost32(option.value + i*sizeof(uint32_t));
	}
}

void Options::toHost32(Option& option) {
	toHost32(option.value);
}

void Options::toHost32(uint8_t* bytes) {
	uint32_t hostValue = ntohl(*((uint32_t*)bytes));
	memcpy(bytes, &hostValue, sizeof(hostValue));
}

void Options::toNetworkReprezentation() {
	for(unordered_map<uint8_t, Option>::iterator it = options.begin(); it != options.end(); it++) {
		Option& option = it->second;
		tryToSetNetworkBytesOrder(option);
	}
}

void Options::tryToSetNetworkBytesOrder(Option& option) {
	switch(option.code) {
		case SUBNET_MASK: 
			toNetwork32(option);
			break;
		case ROUTERS: 
			toNetworkArray32(option);
			break;
		case DNS_OPTION: 
			toNetworkArray32(option);
			break;
		case REQUESTED_IP_ADDRESS: 
			toNetwork32(option);
			break;
		case IP_ADDRESS_LEASE_TIME: 
			toNetwork32(option);
			break;
		case SERVER_IDENTIFIER: 
			toNetwork32(option);
			break;
		default:
			break;
	}
}

void Options::toNetworkArray32(Option& option) {
	for(unsigned i = 0; i < option.length; i += sizeof(uint32_t)) {
		toNetwork32(option.value + i*sizeof(uint32_t));
	}
}

void Options::toNetwork32(Option& option) {
	toNetwork32(option.value);
}

void Options::toNetwork32(uint8_t* bytes) {
	uint32_t networkValue = htonl(*((uint32_t*)bytes));
	memcpy(bytes, &networkValue, sizeof(networkValue));
}

Option& Options::get(uint8_t code) {
	return options[code];
}

bool Options::exists(uint8_t code) {
	return options.find(code) != options.end();
}
