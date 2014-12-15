#include "CommandUpdateScore.hpp"

CommandUpdateScore::CommandUpdateScore(void) : mId(0), mPseudo(""), mScore(0) {
}

CommandUpdateScore::~CommandUpdateScore(void) {
}

uint64_t CommandUpdateScore::getId(void) const {
	return mId;
}

const std::string &CommandUpdateScore::getPseudo(void) const {
	return mPseudo;
}

uint64_t CommandUpdateScore::getScore(void) const {
	return mScore;
}

void CommandUpdateScore::setId(uint64_t id) {
	mId = id;
}

void CommandUpdateScore::setPseudo(const std::string &pseudo) {
	mPseudo = pseudo;
}

void CommandUpdateScore::setScore(uint64_t score) {
	mScore = score;
}

ICommand::Instruction	CommandUpdateScore::getInstruction(void) const {
	return ICommand::Instruction::UPDATE_SCORE;
}
