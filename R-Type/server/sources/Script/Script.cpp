#include "Script.hpp"

Script::Script(void) : mIndex(0) {
}

Script::~Script(void) {
	for(auto &command : mCommands)
        delete command;
	mCommands.clear();
}

Script::Script(const Script &other) {
    std::cout << "Script::Script(const Script &other) copying..." << std::endl;
	if (this != &other) {
		mIndex = 0;
		mCommands = other.getCommands();
        std::cout << "Script::Script(const Script &other) done." << std::endl;
	}
}

const Script &Script::operator=(const Script &other) {
    std::cout << "const Script &Script::operator=(const Script &other) copying..." << std::endl;
	if (this != &other) {
		mIndex = 0;
		mCommands = other.getCommands();
        std::cout << "const Script &Script::operator=(const Script &other) done." << std::endl;
	}
	return *this;
}

std::shared_ptr<Script> Script::clone(void) const
{
    return std::make_shared<Script>(*this);
}

void Script::setCommands(const std::vector<const IScriptCommand*>& commands) {
	mCommands = commands;
}

const std::vector<const IScriptCommand*>& Script::getCommands(void) const {
	return mCommands;
}

const IScriptCommand* Script::currentCommand(void) const {
	return mCommands.at(mIndex);
}

bool Script::isFinish(void) const {
	return mIndex == mCommands.size();
}

void Script::goToNextCommand(void) {
	++mIndex;
}
