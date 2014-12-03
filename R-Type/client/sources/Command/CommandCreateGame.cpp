#include "CommandCreateGame.hpp"
#include "CommandException.hpp"
#include <algorithm>
#include <cstring>

IClientSocket::Message CommandCreateGame::getMessage(void) const {
	CommandCreateGame::PacketFromClient packet;
	std::memset(&packet, 0, sizeof(CommandCreateGame::PacketFromClient));

	std::copy(mName.begin(), mName.begin() + std::min(mName.size(), sizeof(packet.name) - 1), packet.name);
	std::copy(mLevelName.begin(), mLevelName.begin() + std::min(mLevelName.size(), sizeof(packet.levelName) - 1), packet.levelName);
	packet.nbPlayers = mNbPlayers;
	packet.nbSpectators = mNbSpectators;

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandCreateGame::PacketFromClient);

	return message;
}

unsigned int CommandCreateGame::getSizeToRead(void) const {
	throw CommandException("This command can not be receive by the client");
}

void CommandCreateGame::initFromMessage(const IClientSocket::Message & /*message*/) {
	throw CommandException("This command can not be receive by the client");
}
