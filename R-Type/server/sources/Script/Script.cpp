#include "Script.hpp"

NGame::Script::Script(const std::vector<const IScriptCommand*>& commands) : mCommands(commands), mSize(commands.size()) {

}

NGame::Script::~Script(void) {
	for(auto &command : mCommands)
        delete command;
	mCommands.clear();
}

NGame::Script::Script(const NGame::Script& rhs) {
    if (this != &rhs) {
        for (size_t i = 0; i < mCommands.size(); ++i)
            delete mCommands[i];
        mCommands.clear();
        auto& commands = rhs.getCommands();
        mSize = commands.size();
        for (std::size_t i = 0; i < mSize; ++i) {
            auto command = commands[i]->clone();
            mCommands.push_back(command);
        }
    }
}

NGame::Script& NGame::Script::operator = (const NGame::Script& rhs) {
    if (this != &rhs) {
        for (size_t i = 0; i < mCommands.size(); ++i)
            delete mCommands[i];
        mCommands.clear();
        auto& commands = rhs.getCommands();
        mSize = commands.size();
        for (std::size_t i = 0; i < mSize; ++i) {
            auto command = commands[i]->clone();
            mCommands.push_back(command);
        }
    }
    return *this;
}

const std::vector<const IScriptCommand*>& NGame::Script::getCommands(void) const {
    return mCommands;
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