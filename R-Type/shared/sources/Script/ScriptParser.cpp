#include "Parser.hpp"
#include "ScriptParser.hpp"
#include "ScriptException.hpp"
#include "ScriptName.hpp"
#include "ScriptAddCron.hpp"
#include "ScriptAction.hpp"
#include "ScriptRemoveCron.hpp"
#include "ScriptRequire.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <memory>
#include <algorithm>

const ScriptParser::tokenExec ScriptParser::tokenExecTab[] = {
	{ "name", &ScriptParser::cmdName },
	{ "require", &ScriptParser::cmdRequire },
	{ "action", &ScriptParser::cmdAction },
	{ "add_cron", &ScriptParser::cmdAddCron },
	{ "remove_cron", &ScriptParser::cmdRemoveCron }
};

const ScriptParser::MonsterCmd ScriptParser::MonsterCmdTab[] = {
	{ "spawnMobAt", &ScriptParser::fctSpawnMob},
	{ "moveMobTo",  &ScriptParser::fctMoveMob}
};

ScriptParser::ScriptParser(void) {

}

ScriptParser::~ScriptParser(void) {

}

Script ScriptParser::parseFile(std::ifstream &file){
	std::string lineContent;
	std::string wordContent;
	Script script;
    std::string textScript;

	while (file && std::getline(file, lineContent)){
		if (lineContent.length() == 0) 
			continue;
        textScript += lineContent + "\n";
		parser.setStringToParse(lineContent);
		bool rightCmd = false;
		wordContent = parser.extractWord();
		for (const auto &instr : tokenExecTab) {
			if (instr.cmd == wordContent) {
				try {
					script << (this->*instr.Ptr)();
				}
				catch (const std::exception& e) {
					throw ScriptException(e.what());
				}
				rightCmd = true;
			}
		}
		if (rightCmd == false)
			throw ScriptException("Wrong Command Action");
	}
    script.setTextScript(textScript);

	/*
	std::cout << "AVANT:" << std::endl;
	for (const auto& command : script.getCommands())
		std::cout << command->getFrame() << " ";
	std::cout << std::endl;

	std::sort(
		script.getCommands().begin(), 
		script.getCommands().end(), 
		[] (const std::shared_ptr<IScriptCommand> &lhs, const std::shared_ptr<IScriptCommand> &rhs)
		{
			return true;
		}
	);

	std::cout << "APRES:" << std::endl;
	for (const auto& command : script.getCommands())
		std::cout << command->getFrame() << " ";
	std::cout << std::endl;
	*/

	return script;
}

std::shared_ptr<IScriptCommand> ScriptParser::cmdName(void){
	auto command = std::make_shared<ScriptName>();

	command->setName(parser.extractWord());

	return command;
}

std::shared_ptr<IScriptCommand>		ScriptParser::cmdRequire(void){
	auto command = std::make_shared<ScriptRequire>();

	command->setRessourceName(parser.extractWord());

	return command;
}

std::shared_ptr<IScriptCommand>		ScriptParser::cmdAddCron(void){
	auto command = std::make_shared<ScriptAddCron>();

	command->setAddCronFrame(parser.extractValue<double>());
	command->setAddCronTimer(parser.extractValue<double>());
	command->setAddCronIdCron(parser.extractValue<int>());
	command->setAddCronFireMob(parser.extractWord());
	command->setAddCronIdMonster(parser.extractValue<int>());
	command->setAddCronAngle(parser.extractValue<short>());

	return command;
}

std::shared_ptr<IScriptCommand>		ScriptParser::cmdRemoveCron(void){
	auto command = std::make_shared<ScriptRemoveCron>();

	command->setRemoveCronFrame(parser.extractValue<double>());
	command->setRemoveCronIdCron(parser.extractValue<int>());
	return command;
}

std::shared_ptr<IScriptCommand>		ScriptParser::cmdAction(void){
	auto command = std::make_shared<ScriptAction>();

	command->setActionFrame(parser.extractValue<double>());
	command->setActionMobAction(parser.extractWord());

	for (const auto &instr : MonsterCmdTab)
		if (instr.mobAction == command->getActionMobAction())
			command->setActionParams((this->*instr.ftPtr)());
	
	return command;
}

std::shared_ptr<ScriptAction::IActionType> ScriptParser::fctSpawnMob(void){
	auto params = std::make_shared<ScriptAction::SpawnMob>();

	params->setActionIdMonster(parser.extractValue<int>());
	params->setActionName(parser.extractWord());
	params->setActionXpos(parser.extractValue<double>());
	params->setActionYpos(parser.extractValue<double>());
	params->setActionAngle(parser.extractValue<short>());

	return params;
}

std::shared_ptr<ScriptAction::IActionType> ScriptParser::fctMoveMob(void){
	auto params = std::make_shared<ScriptAction::MoveMob>();

	params->setActionIdMonster(parser.extractValue<int>());
	params->setActionAngle(parser.extractValue<short>());

	return params;
}
