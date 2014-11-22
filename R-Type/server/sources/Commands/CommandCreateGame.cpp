#include "CommandCreateGame.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandCreateGame::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandCreateGame::getSizeToRead(void) const {
	return sizeof(CommandCreateGame::PacketFromClient);
}

void CommandCreateGame::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandCreateGame::PacketFromClient))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandCreateGame::PacketFromClient *>(message.msg.data());

	packet.name[sizeof(packet.name) - 1] = 0;
	packet.levelName[sizeof(packet.levelName) - 1] = 0;

	mName = packet.name;
	mLevelName = packet.levelName;
	mNbPlayers = packet.nbPlayers;
	mNbSpectators = packet.nbSpectators;
}
