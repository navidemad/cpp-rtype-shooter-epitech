#include "CommandShowLevel.hpp"
#include "CommandException.hpp"
#include <algorithm>
#include <cstring>

IClientSocket::Message CommandShowLevel::getMessage(void) const {
	CommandShowLevel::PacketFromServer packet;
	std::memset(&packet, 0, sizeof(CommandShowLevel::PacketFromServer));
	std::copy(mName.cbegin(), mName.cbegin() + std::min(mName.size(), sizeof(packet.name) - 1), packet.name);

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandShowLevel::PacketFromServer);

	return message;
}

unsigned int CommandShowLevel::getSizeToRead(void) const {
	throw CommandException("This command can not be received by the server");
}

void CommandShowLevel::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("This command can not be received by the server");
}
