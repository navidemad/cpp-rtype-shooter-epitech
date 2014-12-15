#include "Script.hpp"

Script::Script(void) : mIndex(0) {

}

Script::~Script(void) {
	mCommands.clear();
}

Script::Script(const Script &other) {
	if (this != &other)
	{
		mIndex = other.getIndex();
		mCommands = other.getCommands();
		mTextScript = other.getTextScript();
	}
}

const Script &Script::operator=(const Script &other) {
	if (this != &other)
	{
		mIndex = other.getIndex();
		mCommands = other.getCommands();
		mTextScript = other.getTextScript();
	}
	return *this;
}

const Script &Script::operator<<(std::shared_ptr<IScriptCommand> command) {
	mCommands.push_back(command);
	return *this;
}

size_t Script::getIndex(void) const {
	return mIndex;
}

bool Script::end(void) const {
	return mCommands.size() == 0 || mIndex == mCommands.size() - 1;
}

// faut peut etre retourner une copie du vector mais faire une copie de vector de shared_ptr ça fait des références cyclique je crois
// simon check ça
const std::vector<std::shared_ptr<IScriptCommand>>& Script::getCommands(void) const {
	return mCommands;
}

const std::string& Script::getTextScript(void) const {
    return mTextScript;
}

void Script::setTextScript(const std::string& textScript) {
    mTextScript = textScript;
}

std::shared_ptr<IScriptCommand> Script::currentAction(void) const {
	return mCommands.at(mIndex);
}

bool Script::goToNextAction(void) {
	if (mIndex == mCommands.size() - 1)
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
