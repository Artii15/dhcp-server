#include "../inc/sender.h"

Sender::Sender(libnet_t* lnetHandle) {
	this->lnetHandle = lnetHandle;
}

void Sender::send(DHCPMessage request, const AllocatedAddress&) {

}
