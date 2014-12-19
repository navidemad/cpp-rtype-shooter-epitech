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

std::vector<AScriptCommand> ScriptParser::parseFile(std::ifstream &file) {

	std::vector<AScriptCommand> commands;

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

	std::sort(commands.begin(), commands.end(), [](const AScriptCommand& left, const AScriptCommand& right) { return left.getFrame() < right.getFrame(); });
	return commands;
}

AScriptCommand ScriptParser::commandScriptName(void) {
	double frame = 0;
	ScriptName command(frame);
	command.setStageName(mParser.extractWord());
	return command;
}

AScriptCommand ScriptParser::commandScriptRequire(void) {
	double frame = 0;
	ScriptRequire command(frame);
    command.setRessourceName(mParser.extractWord());
	return command;
}

AScriptCommand ScriptParser::commandScriptSpawn(void) {
	double frame = mParser.extractValue<double>();
	ScriptSpawn command(frame);
	command.setSpawnName(mParser.extractWord());
    command.setX(mParser.extractValue<double>());
	command.setY(mParser.extractValue<double>());
    command.setAngle(mParser.extractValue<double>());
	return command;
}
