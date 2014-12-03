#include "CommandDeleteGame.hpp"
#include "CommandException.hpp"
#include <algorithm>
#include <cstring>

IClientSocket::Message CommandDeleteGame::getMessage(void) const {
	CommandDeleteGame::PacketFromClient packet;
	std::memset(&packet, 0, sizeof(CommandDeleteGame::PacketFromClient));

	std::copy(mName.begin(), mName.begin() + std::min(mName.size(), sizeof(packet.name) - 1), packet.name);

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandDeleteGame::PacketFromClient);

	return message;
}

unsigned int CommandDeleteGame::getSizeToRead(void) const {
	throw CommandException("This command can not be receive by the client");
}

void CommandDeleteGame::initFromMessage(const IClientSocket::Message & /*message*/) {
	throw CommandException("This command can not be receive by the client");
}