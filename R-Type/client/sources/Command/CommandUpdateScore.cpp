#include "CommandUpdateScore.hpp"
#include <algorithm>
#include <cstring>

IClientSocket::Message CommandUpdateScore::getMessage(void) const {
	throw CommandException("This command can not be sent by the server");
}

unsigned int CommandUpdateScore::getSizeToRead(void) const {
	return sizeof(CommandUpdateScore::PacketFromServer);
}

void CommandUpdateScore::initFromMessage(const IClientSocket::Message &) {
	if (message.msgSize != sizeof(CommandUpdateScore::PacketFromServer))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandUpdateScore::PacketFromServer *>(message.msg.data());

	packet.pseudo[sizeof(packet.pseudo) - 1] = 0;

	mPseudo = packet.pseudo;
	mId = packet.id;
	mScore = packet.score;
}
