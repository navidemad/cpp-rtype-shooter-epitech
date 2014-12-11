#include "Script.hpp"

Script::Script(void) {

}

Script::~Script(void) {
	mCommands.clear();
}
#include <iostream>
Script::Script(const Script &other) {
	if (this != &other)
	{
		std::cout << "copy constructor" << std::endl;
		mCommands = other.getCommands(); // attention copy of std vector de shared_ptr du coup le ref_count est incrémenté !!
		//mCommands.insert(mCommands.begin(), other.getCommands().begin(), other.getCommands().end());
		mTextScript = other.getTextScript();
	}
}

const Script &Script::operator=(const Script &other) {
	if (this != &other)
	{
		mCommands = other.getCommands();
		//mCommands.insert(mCommands.begin(), other.getCommands().begin(), other.getCommands().end());
		mTextScript = other.getTextScript();
	}
	return *this;
}

void Script::addAction(std::shared_ptr<IScriptCommand> command) {
	mCommands.push_back(command);
}

const std::vector<std::shared_ptr<IScriptCommand>>& Script::getCommands(void) const {
	return mCommands;
}

const std::string& Script::getTextScript(void) const {
    return mTextScript;
}

void Script::setTextScript(const std::string& textScript) {
    mTextScript = textScript;
}
