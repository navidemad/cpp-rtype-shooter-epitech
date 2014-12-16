#include "CommandFire.hpp"
#include "CommandException.hpp"
#include <iostream> // a supprimer
IClientSocket::Message CommandFire::getMessage(void) const {
	std::cout << "CommandFire::" << __FUNCTION__ << std::endl;
	IClientSocket::Message message;
	message.msg.clear();
	message.msgSize = 0;

	return message;
}

unsigned int CommandFire::getSizeToRead(void) const {
	throw CommandException("This command can not be receive by the client");
}

void CommandFire::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("This command can not be receive by the client");
}
