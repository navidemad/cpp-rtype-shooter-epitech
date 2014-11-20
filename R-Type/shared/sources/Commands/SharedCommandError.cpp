#include "CommandError.hpp"

CommandError::CommandError(void) : mInstructionCode(ICommand::Instruction::UNKNOWN), mErrorCode(ErrorStatus::Error::UNKNOWN) {
}

CommandError::~CommandError(void) {
}

ICommand::Instruction CommandError::getInstructionCode(void) const {
	return mInstructionCode;
}

ErrorStatus::Error CommandError::getErrorCode(void) const {
	return mErrorCode;
}

void	CommandError::setInstructionCode(ICommand::Instruction instruction) {
	mInstructionCode = instruction;
}

void	CommandError::setErrorCode(ErrorStatus::Error error) {
	mErrorCode = error;
}

ICommand::Instruction	CommandError::getInstruction(void) const {
	return ICommand::Instruction::ERROR;
}
