#include "CommandShowGame.hpp"
#include <algorithm>
#include <cstring>

IClientSocket::Message CommandShowGame::getMessage(void) const {
	CommandShowGame::PacketFromServer packet;
	std::memset(&packet, 0, sizeof(CommandShowGame::PacketFromClient));

	std::copy(mName.begin(), mName.begin() + std::min(mName.size(), sizeof(packet.name) - 1), packet.name);

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandShowGame::PacketFromClient);

	return message;
}

unsigned int CommandShowGame::getSizeToRead(void) const {
	return sizeof(CommandShowGame::PacketFromServer);
}

void CommandShowGame::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandShowGame::PacketFromServer))
		throw std::string("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandShowGame::PacketFromServer *>(message.msg.data());

	packet.name[sizeof(packet.name) - 1] = 0;
	packet.levelName[sizeof(packet.levelName) - 1] = 0;

	mName = packet.name;
	mLevelName = packet.levelName;
	mNbPlayers = packet.nbPlayers;
	mMaxPlayers = packet.maxPlayers;
	mNbObservers = packet.nbObservers;
	mMaxObservers = packet.maxObservers;
}