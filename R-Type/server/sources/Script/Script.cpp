#include "Script.hpp"

Script::Script(const Script &other) {
	if (this != &other)
		mCommands = other.getCommands();
}

const Script &Script::operator=(const Script &other) {
	if (this != &other)
		mCommands = other.getCommands();
	return *this;
}

void Script::setCommands(const std::vector<AScriptCommand>& commands) {
	mCommands = commands;
	mCurrentIterator = mCommands.begin();
}

const std::vector<AScriptCommand>& Script::getCommands(void) const {
	return mCommands;
}

const AScriptCommand& Script::currentAction(void) const {
	return *mCurrentIterator;
}

bool Script::goToNextAction(void) {
	if (mCurrentIterator == mCommands.end())
		return false;
	++mCurrentIterator;
	return true;
}
