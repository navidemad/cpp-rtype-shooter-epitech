#include "Script.hpp"

NGame::Script::Script(const std::vector<const IScriptCommand*>& commands) : mCommands(commands), mSize(commands.size()), mIndex(0) {

}

NGame::Script::~Script(void) {
	for(auto &command : mCommands)
        delete command;
	mCommands.clear();
}

NGame::Script::Script(const NGame::Script& rhs) {
    if (this != &rhs)
        deepCopy(rhs);
}

const NGame::Script& NGame::Script::operator = (const NGame::Script& rhs) {
    if (this != &rhs)
        deepCopy(rhs);
    return *this;
}

void NGame::Script::deepCopy(const NGame::Script& rhs) {
    for (size_t i = 0; i < mCommands.size(); ++i)
        delete mCommands[i];
    mCommands.clear();
    auto& commands = rhs.getCommands();
    mSize = commands.size();
    for (std::size_t i = 0; i < mSize; ++i) {
        auto command = commands[i]->clone();
        mCommands.push_back(command);
    }
    mIndex = 0;
}

const std::vector<const IScriptCommand*>& NGame::Script::getCommands(void) const {
    return mCommands;
}

const IScriptCommand* NGame::Script::currentCommand(void) const {
    return mCommands.at(mIndex);
}

bool NGame::Script::isFinish(void) const {
    return mIndex == mSize;
}

void NGame::Script::goToNextCommand(void) {
    ++mIndex;
}
