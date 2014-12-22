#include "Script.hpp"


Script::~Script(void) {
	for(auto &command : mCommands)
        delete command;
	mCommands.clear();
}

Script& Script::operator=(const std::vector<const IScriptCommand*>& commands) {
	mCommands = commands;
    mSize = commands.size();
    return *this;
}

bool Script::last(unsigned int index) const {
    return index == mSize;
}

const IScriptCommand* Script::get(unsigned int index) const {
	return mCommands.at(index);
}

unsigned int Script::size(void) const {
    return mCommands.size();
}