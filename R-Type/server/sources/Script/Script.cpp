#include "Script.hpp"

NGame::Script::~Script(void) {
	for(auto &command : mCommands)
        delete command;
	mCommands.clear();
}

NGame::Script& NGame::Script::operator=(const std::vector<const IScriptCommand*>& commands) {
	mCommands = commands;
    mSize = commands.size();
    return *this;
}

bool NGame::Script::last(unsigned int index) const {
    return index == mSize;
}

const IScriptCommand* NGame::Script::get(unsigned int index) const {
	return mCommands.at(index);
}

unsigned int NGame::Script::size(void) const {
    return mCommands.size();
}