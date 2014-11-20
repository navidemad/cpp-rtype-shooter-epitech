#include "CommandUpdateScore.hpp"

CommandUpdateScore::CommandUpdateScore(void) : mId(0), mPseudo(""), mScore(0) {
}

CommandUpdateScore::~CommandUpdateScore(void) {
}

int CommandUpdateScore::getId(void) const {
	return mId;
}

const std::string &CommandUpdateScore::getPseudo(void) const {
	return mPseudo;
}

int CommandUpdateScore::getScore(void) const {
	return mScore;
}

void CommandUpdateScore::setId(int id) {
	mId = id;
}

void CommandUpdateScore::setPseudo(const std::string &pseudo) {
	mPseudo = pseudo;
}

void CommandUpdateScore::setScore(int score) {
	mScore = score;
}

ICommand::Instruction	CommandUpdateScore::getInstruction(void) const {
	return ICommand::Instruction::UPDATE_SCORE;
}
