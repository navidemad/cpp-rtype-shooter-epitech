#include "CommandUpdateScore.hpp"
#include "CommandException.hpp"
#include <algorithm>
#include <cstring>

IClientSocket::Message CommandUpdateScore::getMessage(void) const {
	CommandUpdateScore::PacketFromServer packet;
	std::memset(&packet, 0, sizeof(CommandUpdateScore::PacketFromServer));
	std::copy(mPseudo.cbegin(), mPseudo.cbegin() + std::min(mPseudo.size(), sizeof(packet.pseudo) - 1), packet.pseudo);
	packet.id = mId;
	packet.score = mScore;

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandUpdateScore::PacketFromServer);

	return message;
}

unsigned int CommandUpdateScore::getSizeToRead(void) const {
	throw CommandException("This command can not be received by the server");
}

void CommandUpdateScore::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("This command can not be received by the server");
}
