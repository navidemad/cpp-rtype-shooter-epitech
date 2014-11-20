#include "CommandUpdatePseudo.hpp"

CommandUpdatePseudo::CommandUpdatePseudo(void) : mPseudo("") {
}

CommandUpdatePseudo::~CommandUpdatePseudo(void) {
}

const std::string &CommandUpdatePseudo::getPseudo(void) const {
	return mPseudo;
}

void CommandUpdatePseudo::setPseudo(const std::string &pseudo) {
	mPseudo = pseudo;
}

ICommand::Instruction	CommandUpdatePseudo::getInstruction(void) const {
	return ICommand::Instruction::UPDATE_PSEUDO;
}
