#include "ScriptParser.hpp"
#include "ScriptException.hpp"
#include <string>
#include <fstream>
#include <algorithm>

const ScriptParser::tokenExec ScriptParser::tokenExecTab[] = {
    { "spawn", &ScriptParser::commandScriptSpawn },
	{ "", nullptr }
};

std::shared_ptr<NGame::Script> ScriptParser::createScriptFromFile(std::ifstream &file) {

	std::vector<const IScriptCommand*> commands;

	std::string lineContent;

	while (file && std::getline(file, lineContent)) {
		if (lineContent.length() == 0)
			continue;
		else if (lineContent.find("#") != std::string::npos)
			continue;
		else if (lineContent.find("//") != std::string::npos)
			continue;
		mParser.setStringToParse(lineContent);
		const std::string wordContent = mParser.extractWord();
		for (const auto &instr : tokenExecTab) {
			if (instr.cmd == wordContent) {
				try { commands.push_back((this->*instr.Ptr)()); break; }
				catch (const std::exception& e) { throw ScriptException(e.what()); }
			}
			else if (instr.cmd.empty()) {
				throw ScriptException("Syntax error\n\t>> " + lineContent);
			}
		}
	}

	if (commands.size() == 0)
		throw ScriptException("File haven't commands");

	std::sort(commands.begin(), commands.end(), [](const IScriptCommand* left, const IScriptCommand* right) { return left->getFrame() < right->getFrame(); });

    return std::make_shared<NGame::Script>(commands);
}

const IScriptCommand* ScriptParser::commandScriptSpawn(void) {
	auto command = new ScriptSpawn;
    command->setFrame(mParser.extractValue<float>());
	command->setInstruction(IScriptCommand::Instruction::SPAWN);
	command->setSpawnName(mParser.extractWord());
    command->setX(mParser.extractValue<float>());
    command->setY(mParser.extractValue<float>());
    command->setAngle(mParser.extractValue<float>());
	return command;
}
