#include "CommandMove.hpp"

CommandMove::CommandMove(void) : mDirection(IRessource::Direction::UNKNOWN) {
}

CommandMove::~CommandMove(void) {
}

IRessource::Direction CommandMove::getDirection(void) const {
	return mDirection;
}

void CommandMove::setDirection(IRessource::Direction direction) {
	mDirection = direction;
}

ICommand::Instruction	CommandMove::getInstruction(void) const {
	return ICommand::Instruction::MOVE;
}
