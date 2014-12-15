#include "CommandTimeElapsedPing.hpp"

CommandTimeElapsedPing::CommandTimeElapsedPing(void) : mTimeElapsed(0) {
}

CommandTimeElapsedPing::~CommandTimeElapsedPing(void) {
}

double CommandTimeElapsedPing::getTimeElapsed(void) const {
	return mTimeElapsed;
}

void CommandTimeElapsedPing::setTimeElapsed(double timeElapsed) {
	mTimeElapsed = timeElapsed;
}

ICommand::Instruction	CommandTimeElapsedPing::getInstruction(void) const {
	return ICommand::Instruction::TIME_ELAPSED_PING;
}
