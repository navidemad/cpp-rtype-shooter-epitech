#include "CommandMove.hpp"

IClientSocket::Message CommandMove::getMessage(void) const {
	CommandMove::PacketFromClient packet;
	std::memset(&packet, 0, sizeof(CommandMove::PacketFromClient));

	packet.direction = static_cast<char>(mDirection);

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandMove::PacketFromClient);

	return message;
}

unsigned int CommandMove::getSizeToRead(void) const {
	throw std::string("This command can not be receive by the client");
}

void CommandMove::initFromMessage(const IClientSocket::Message &message) {
	throw std::string("This command can not be receive by the client");
}