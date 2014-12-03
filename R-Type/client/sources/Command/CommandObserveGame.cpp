#include "CommandObserveGame.hpp"
#include "CommandException.hpp"
#include <cstring>
#include <algorithm>

IClientSocket::Message CommandObserveGame::getMessage(void) const {
	CommandObserveGame::PacketFromClient packet;
	std::memset(&packet, 0, sizeof(CommandObserveGame::PacketFromClient));

	std::copy(mName.begin(), mName.begin() + std::min(mName.size(), sizeof(packet.name) - 1), packet.name);

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandObserveGame::PacketFromClient);

	return message;
}

unsigned int CommandObserveGame::getSizeToRead(void) const {
	throw CommandException("This command can not be receive by the client");
}

void CommandObserveGame::initFromMessage(const IClientSocket::Message & /*message*/) {
	throw CommandException("This command can not be receive by the client");
}