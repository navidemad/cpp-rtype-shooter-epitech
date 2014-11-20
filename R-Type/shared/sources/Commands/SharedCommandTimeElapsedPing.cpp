#include "CommandTimeElapsedPing.hpp"

CommandTimeElapsedPing::CommandTimeElapsedPing(void) : mTimeElapsed(0) {
}

CommandTimeElapsedPing::~CommandTimeElapsedPing(void) {
}

int64_t CommandTimeElapsedPing::getTimeElapsed(void) const {
	return mTimeElapsed;
}

void CommandTimeElapsedPing::setTimeElapsed(int64_t timeElapsed) {
	mTimeElapsed = timeElapsed;
}

ICommand::Instruction	CommandTimeElapsedPing::getInstruction(void) const {
	return ICommand::Instruction::TIME_ELAPSED_PING;
}
