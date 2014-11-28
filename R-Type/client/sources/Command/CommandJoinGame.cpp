#include "CommandJoinGame.hpp"

IClientSocket::Message CommandJoinGame::getMessage(void) const {
	CommandJoinGame::PacketFromServer packet;
	std::memset(&packet, 0, sizeof(CommandJoinGame::PacketFromServer));

	std::copy(mName.begin(), mName.begin() + std::min(mName.size(), sizeof(packet.name) - 1), packet.name);

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandJoinGame::PacketFromServer);

	return message;
}

unsigned int CommandJoinGame::getSizeToRead(void) const {
	throw std::string("This command can not be receive by the client");
}

void CommandJoinGame::initFromMessage(const IClientSocket::Message &message) {
	throw std::string("This command can not be receive by the client");
}