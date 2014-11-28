#include "CommandUpdatePseudo.hpp"

IClientSocket::Message CommandUpdatePseudo::getMessage(void) const {
	CommandCreateGame::PacketFromClient packet;
	std::memset(&packet, 0, sizeof(CommandCreateGame::PacketFromClient));

	std::copy(mPseudo.begin(), mPseudo.begin() + std::min(mPseudo.size(), sizeof(packet.pseudo) - 1), packet.pseudo);

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandCreateGame::PacketFromClient);

	return message;
}

unsigned int CommandUpdatePseudo::getSizeToRead(void) const {
	throw std::string("This command can not be receive by the client");
}

void CommandUpdatePseudo::initFromMessage(const IClientSocket::Message &message) {
	throw std::string("This command can not be receive by the client");
}