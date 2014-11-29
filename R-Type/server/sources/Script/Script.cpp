#include "Script.hpp"

Script::Script(void) : mIndex(0) {

}

Script::~Script(void) {
	mCommands.clear();
}

void Script::addAction(std::shared_ptr<IScriptCommand> command) {
	mCommands.push_back(command);
}

std::shared_ptr<IScriptCommand> Script::currentAction(void) const {
	return mCommands.at(mIndex);
}

std::vector<std::shared_ptr<IScriptCommand>> Script::getCommands(void) const {
	return mCommands;
}

bool Script::goToNextAction(void) {
	if (mIndex >= mCommands.size())
		return false;

	++mIndex;
	return true;
}

bool Script::goToPrevAction(void) {
	if (mIndex == 0)
		return false;

	--mIndex;
	return true;
}

void Script::restart(void) {
	mIndex = 0;
}

