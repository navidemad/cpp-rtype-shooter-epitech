#include "CommandMoveResource.hpp"

CommandMoveResource::CommandMoveResource(void) : mId(0), mType(IResource::Type::UNKNOWN), mX(0), mY(0), mAngle(0) {
}

CommandMoveResource::~CommandMoveResource(void) {
}

uint64_t CommandMoveResource::getId(void) const {
	return mId;
}

IResource::Type CommandMoveResource::getType(void) const {
	return mType;
}

short CommandMoveResource::getX(void) const {
	return mX;
}

short CommandMoveResource::getY(void) const {
	return mY;
}

short CommandMoveResource::getAngle(void) const {
	return mAngle;
}

void	CommandMoveResource::setId(uint64_t id) {
	mId = id;
}

void	CommandMoveResource::setType(IResource::Type type) {
	mType = type;
}

void	CommandMoveResource::setX(short x) {
	mX = x;
}

void	CommandMoveResource::setY(short y) {
	mY = y;
}

void	CommandMoveResource::setAngle(short angle) {
	mAngle = angle;
}

ICommand::Instruction	CommandMoveResource::getInstruction(void) const {
	return ICommand::Instruction::MOVE_RESOURCE;
}
