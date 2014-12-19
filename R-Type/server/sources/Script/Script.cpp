#include "Script.hpp"

Script::Script(void) : mIndex(0) {

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

void Script::setCommands(const std::vector<AScriptCommand>& commands) {
	mCommands = commands;
}

const std::vector<AScriptCommand>& Script::getCommands(void) const {
	return mCommands;
}

const AScriptCommand& Script::currentCommand(void) const {
	return mCommands.at(mIndex);
}

bool Script::isFinish(void) const {
	return mIndex == mCommands.size();
}

void Script::goToNextCommand(void) {
	++mIndex;
}
