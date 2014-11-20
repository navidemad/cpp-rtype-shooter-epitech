#include "CommandDestroyResource.hpp"

IClientSocket::Message CommandDestroyResource::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandDestroyResource::getSizeToRead(void) const {
	return 0;
}

void CommandDestroyResource::initFromMessage(const IClientSocket::Message &) {
}
