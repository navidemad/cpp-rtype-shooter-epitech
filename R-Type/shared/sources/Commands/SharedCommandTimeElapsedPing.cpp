#include "CommandTimeElapsedPing.hpp"

CommandTimeElapsedPing::CommandTimeElapsedPing(void) : mTimeElapsed(0.f) {
}

CommandTimeElapsedPing::~CommandTimeElapsedPing(void) {
}

float CommandTimeElapsedPing::getTimeElapsed(void) const {
	return mTimeElapsed;
}

void CommandTimeElapsedPing::setTimeElapsed(float timeElapsed) {
	mTimeElapsed = timeElapsed;
}

ICommand::Instruction	CommandTimeElapsedPing::getInstruction(void) const {
	return ICommand::Instruction::TIME_ELAPSED_PING;
}
