#include "Script.hpp"

Script::Script(void) : mIndex(0) {

}

Script::~Script(void) {
	for(auto &command : mCommands)
        delete command;
	mCommands.clear();
}

Script::Script(const Script &other) {
	if (this != &other) {
		mIndex = 0;
		mCommands = other.getCommands();
	}
}

const Script &Script::operator=(const Script &other) {
	if (this != &other) {
		mIndex = 0;
		mCommands = other.getCommands();
	}
	return *this;
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
