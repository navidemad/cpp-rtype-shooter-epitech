#include "CommandShowLevel.hpp"

CommandShowLevel::CommandShowLevel(void) : mName(""), mScript("") {
}

CommandShowLevel::~CommandShowLevel(void) {
}

const std::string &CommandShowLevel::getName(void) const {
	return mName;
}

const std::string &CommandShowLevel::getScript(void) const {
	return mScript;
}

void CommandShowLevel::setName(const std::string &name) {
	mName = name;
}

void CommandShowLevel::setScript(const std::string &script) {
	mScript = script;
}

ICommand::Instruction	CommandShowLevel::getInstruction(void) const {
	return ICommand::Instruction::SHOW_LEVEL;
}
