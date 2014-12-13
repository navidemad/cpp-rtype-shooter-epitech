#include "CommandMoveResource.hpp"

CommandMoveResource::CommandMoveResource(void) : mId(0), mType(IResource::Type::UNKNOWN), mX(0.0), mY(0.0), mAngle(0) {
}

CommandMoveResource::~CommandMoveResource(void) {
}

uint64_t CommandMoveResource::getId(void) const {
	return mId;
}

IResource::Type CommandMoveResource::getType(void) const {
	return mType;
}

double CommandMoveResource::getX(void) const {
	return mX;
}

double CommandMoveResource::getY(void) const {
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

void	CommandMoveResource::setX(double x) {
	mX = x;
}

void	CommandMoveResource::setY(double y) {
	mY = y;
}

void	CommandMoveResource::setAngle(short angle) {
	mAngle = angle;
}

ICommand::Instruction	CommandMoveResource::getInstruction(void) const {
	return ICommand::Instruction::MOVE_RESOURCE;
}
