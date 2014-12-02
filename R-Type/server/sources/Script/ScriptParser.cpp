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

std::shared_ptr<Script>		ScriptParser::parseFile(std::ifstream &file){
	std::string lineContent;
	std::string wordContent;
	auto		script = std::make_shared<Script>();

	while (file && std::getline(file, lineContent)){
		if (lineContent.length() == 0)continue;
		parser.setStringToParse(lineContent);
		bool rightCmd = false;
			wordContent = parser.extractWord();
			for (const auto &instr : tokenExecTab) {
				if (instr.cmd == wordContent) {
					script->addAction((this->*instr.Ptr)());
					rightCmd = true;
				}
			}
			if (rightCmd == false)
				throw ScriptException("Wrong Command Action");
	}
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

	command->setAddCronFrame(parser.extractValue<int>());
	command->setAddCronTimer(parser.extractValue<int>());
	command->setAddCronIdCron(parser.extractValue<int>());
	command->setAddCronFireMob(parser.extractWord());
	command->setAddCronIdMonster(parser.extractValue<int>());
	command->setAddCronAngle(parser.extractValue<int>());

	return command;
}

std::shared_ptr<IScriptCommand>		ScriptParser::cmdRemoveCron(void){
	auto command = std::make_shared<ScriptRemoveCron>();

	command->setRemoveCronFrame(parser.extractValue<int>());
	command->setRemoveCronIdCron(parser.extractValue<int>());
	return command;
}

std::shared_ptr<IScriptCommand>		ScriptParser::cmdAction(void){
	auto command = std::make_shared<ScriptAction>();

	command->setActionFrame(parser.extractValue<int>());
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
	params->setActionXpos(parser.extractValue<int>());
	params->setActionYpos(parser.extractValue<int>());
	params->setActionAngle(parser.extractValue<int>());

	return params;
}

std::shared_ptr<ScriptAction::IActionType> ScriptParser::fctMoveMob(void){
	auto params = std::make_shared<ScriptAction::MoveMob>();

	params->setActionIdMonster(parser.extractValue<int>());
	params->setActionAngle(parser.extractValue<int>());

	return params;
}
