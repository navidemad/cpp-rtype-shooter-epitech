#include "CommandShowLevel.hpp"

CommandShowLevel::CommandShowLevel(void) : mName("") {
}

CommandShowLevel::~CommandShowLevel(void) {
}

const std::string &CommandShowLevel::getName(void) const {
	return mName;
}

void CommandShowLevel::setName(const std::string &name) {
	mName = name;
}

ICommand::Instruction	CommandShowLevel::getInstruction(void) const {
	return ICommand::Instruction::SHOW_LEVEL;
}
