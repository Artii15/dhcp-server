#ifndef PACKER_H
#define PACKER_H

#include <stdint.h>

class Packer {
	public:
		uint8_t* packIpAddressLeaseTime(uint8_t* dst, uint32_t leaseTime) {
			*(dst++) = IP_ADDRESS_LEASE_TIME;
			*(dst++) = sizeof(leaseTime);

			uint32_t normalizedLeaseTime = htonl(leaseTime);
			memcpy(dst, &normalizedLeaseTime, sizeof(normalizedLeaseTime));

			return dst + sizeof(normalizedLeaseTime);
		}

		uint8_t* packMessageType(uint8_t* dst, uint8_t messageType) {
			*(dst++) = DHCP_MESSAGE_TYPE;
			*(dst++) = sizeof(messageType);
			*(dst++) = messageType;

			return dst;
		}

		uint8_t* packServerIdentifier(uint8_t* dst) {
			*(dst++) = SERVER_IDENTIFIER;
			*(dst++) = sizeof(serverIp);
			memcpy(dst, &serverIp, sizeof(serverIp));

			return dst + sizeof(serverIp);
		}

		uint8_t* packNetworkMask(uint8_t* dst, uint32_t mask) {
			*(dst++) = SUBNET_MASK;
			*(dst++) = sizeof(mask);

			uint32_t normalizedMask = htonl(mask);
			memcpy(dst, &normalizedMask, sizeof(mask));

			return dst + sizeof(mask);
		}

		uint8_t* packRouters(uint8_t* dst, const list<uint32_t>* routers) {
			if(!routers->empty()) {
				*(dst++) = ROUTERS;

				uint32_t routersSizeInBytes = routers->size() * sizeof(uint32_t);
				*(dst++) = routersSizeInBytes;

				for(list<uint32_t>::const_iterator routersIt = routers->begin(); routersIt != routers->end(); routersIt++) {
					uint32_t router = htonl(*routersIt);
					memcpy(dst, &router, sizeof(router));
					dst += sizeof(router);
				}
			}

			return dst;
		}

		uint8_t* packDnsServers(uint8_t* dst, const list<uint32_t>* servers) {
			if(!servers->empty()) {
				*(dst++) = DNS_OPTION;

				uint32_t serversSizeInBytes = servers->size() * sizeof(uint32_t);
				*(dst++) = serversSizeInBytes;

				for(list<uint32_t>::const_iterator serversIt = servers->begin(); serversIt != servers->end(); serversIt++) {
					uint32_t server = htonl(*serversIt);
					memcpy(dst, &server, sizeof(server));
					dst += sizeof(server);
				}
			}

			return dst;
		}
};

#endif
