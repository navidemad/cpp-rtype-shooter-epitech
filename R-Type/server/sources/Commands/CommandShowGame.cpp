#include "CommandShowGame.hpp"
#include "CommandException.hpp"
#include <algorithm>
#include <cstring>

IClientSocket::Message CommandShowGame::getMessage(void) const {
	CommandShowGame::PacketFromServer packet;
	std::memset(&packet, 0, sizeof(CommandShowGame::PacketFromServer));
	std::copy(mName.cbegin(), mName.cbegin() + std::min(mName.size(), sizeof(packet.name) - 1), packet.name);
	std::copy(mLevelName.cbegin(), mLevelName.cbegin() + std::min(mLevelName.size(), sizeof(packet.levelName) - 1), packet.levelName);
	packet.nbPlayers = mNbPlayers;
	packet.maxPlayers = mMaxPlayers;
	packet.nbObservers = mNbObservers;
	packet.maxObservers = mMaxObservers;

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandShowGame::PacketFromServer);

	return message;
}

unsigned int CommandShowGame::getSizeToRead(void) const {
	return sizeof(CommandShowGame::PacketFromClient);
}

void CommandShowGame::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandShowGame::PacketFromClient))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandShowGame::PacketFromClient *>(message.msg.data());

	packet.name[sizeof(packet.name) - 1] = 0;
	mName = packet.name;
}
