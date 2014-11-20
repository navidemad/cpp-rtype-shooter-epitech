#include "CommandMoveResource.hpp"

IClientSocket::Message CommandMoveResource::getMessage(void) const {
	IClientSocket::Message message;

	return message;
}

unsigned int CommandMoveResource::getSizeToRead(void) const {
	return 0;
}

void CommandMoveResource::initFromMessage(const IClientSocket::Message &) {
}
