#include "CommandMoveResource.hpp"
#include "CommandException.hpp"

IClientSocket::Message CommandMoveResource::getMessage(void) const {
	throw CommandException("This command can not be sent by the client");
}

unsigned int CommandMoveResource::getSizeToRead(void) const {
	return sizeof(CommandMoveResource::PacketFromServer);
}

void CommandMoveResource::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof(CommandMoveResource::PacketFromServer))
		throw CommandException("Packet has an invalid size");

	auto packet = *reinterpret_cast<const CommandMoveResource::PacketFromServer *>(message.msg.data());

	mType = static_cast<IResource::Type>(packet.type);
	mX = packet.x;
	mY = packet.y;
	mAngle = packet.angle;
	mId = packet.id;
}