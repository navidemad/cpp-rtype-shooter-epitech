#include "CommandEndGame.hpp"
#include "CommandException.hpp"
#include <algorithm>
#include <cstring>

IClientSocket::Message CommandEndGame::getMessage(void) const {
	CommandEndGame::PacketFromServer packet;
	std::memset(&packet, 0, sizeof(CommandEndGame::PacketFromServer));
	std::copy(mName.begin(), mName.begin() + std::min(mName.size(), sizeof(packet.name) - 1), packet.name);

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandEndGame::PacketFromServer);

	return message;
}

unsigned int CommandEndGame::getSizeToRead(void) const {
	throw CommandException("This command can not be received by the server");
}

void CommandEndGame::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("This command can not be received by the server");
}
