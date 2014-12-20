#include "ScriptParser.hpp"
#include "ScriptException.hpp"
#include <string>
#include <fstream>
#include <algorithm>

const ScriptParser::tokenExec ScriptParser::tokenExecTab[] = {
    { "name", &ScriptParser::commandScriptName },
    { "require", &ScriptParser::commandScriptRequire },
    { "spawn", &ScriptParser::commandScriptSpawn },
	{ "", nullptr }
};

std::shared_ptr<Script> ScriptParser::createScriptFromFile(std::ifstream &file) {

	std::vector<const IScriptCommand*> commands;

	std::string lineContent;

	while (file && std::getline(file, lineContent)) {
		if (lineContent.length()) {
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
	}

	std::sort(commands.begin(), commands.end(), [](const IScriptCommand* left, const IScriptCommand* right) { return left->getFrame() < right->getFrame(); });

	auto script = std::make_shared<Script>();
	script->setCommands(commands);

	return script;
}

const IScriptCommand* ScriptParser::commandScriptName(void) {
	auto command = new ScriptName;
	command->setFrame(0);
	command->setInstruction(IScriptCommand::Instruction::NAME);
	command->setStageName(mParser.extractWord());
	return command;
}

const IScriptCommand* ScriptParser::commandScriptRequire(void) {
	auto command = new ScriptRequire;
	command->setFrame(0);
	command->setInstruction(IScriptCommand::Instruction::REQUIRE);
    command->setRessourceName(mParser.extractWord());
	return command;
}

const IScriptCommand* ScriptParser::commandScriptSpawn(void) {
	auto command = new ScriptSpawn;
	command->setFrame(mParser.extractValue<double>());
	command->setInstruction(IScriptCommand::Instruction::SPAWN);
	command->setSpawnName(mParser.extractWord());
    command->setX(mParser.extractValue<double>());
	command->setY(mParser.extractValue<double>());
    command->setAngle(mParser.extractValue<double>());
	return command;
}
