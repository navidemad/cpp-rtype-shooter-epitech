#include "CommandMoveResource.hpp"

CommandMoveResource::CommandMoveResource(void) : mId(0), mType(IResource::Type::UNKNOWN), mX(0), mY(0), mAngle(0) {
}

CommandMoveResource::~CommandMoveResource(void) {
}

int CommandMoveResource::getId(void) const {
	return mId;
}

IResource::Type CommandMoveResource::getType(void) const {
	return mType;
}

float CommandMoveResource::getX(void) const {
	return mX;
}

float CommandMoveResource::getY(void) const {
	return mY;
}

short CommandMoveResource::getAngle(void) const {
	return mAngle;
}

void	CommandMoveResource::setId(int id) {
	mId = id;
}

void	CommandMoveResource::setType(IResource::Type type) {
	mType = type;
}

void	CommandMoveResource::setX(float x) {
	mX = x;
}

void	CommandMoveResource::setY(float y) {
	mY = y;
}

void	CommandMoveResource::setAngle(short angle) {
	mAngle = angle;
}

ICommand::Instruction	CommandMoveResource::getInstruction(void) const {
	return ICommand::Instruction::MOVE_RESOURCE;
}