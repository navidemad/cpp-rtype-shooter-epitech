#include "CommandMove.hpp"

CommandMove::CommandMove(void) : mDirection(IResource::Direction::UNKNWON) {
}

CommandMove::~CommandMove(void) {
}

IResource::Direction CommandMove::getDirection(void) const {
	return mDirection;
}

void CommandMove::setDirection(IResource::Direction direction) {
	mDirection = direction;
}

ICommand::Instruction	CommandMove::getInstruction(void) const {
	return ICommand::Instruction::MOVE;
}
