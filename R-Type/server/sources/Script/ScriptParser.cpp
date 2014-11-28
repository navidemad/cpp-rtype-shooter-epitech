#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "Parser.hpp"
#include "ScriptParser.hpp"

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

void		ScriptParser::parseFile(std::ifstream &file){
	std::string lineContent;
	std::string wordContent;

	while (file.good()){
		std::getline(file, lineContent);
		parser.setStringToParse(lineContent);
		wordContent = parser.extractWord();
		std::cout << "premier mot : " << wordContent << std::endl;

		for (const auto &instr : tokenExecTab)
			if (instr.cmd == wordContent) {
				(this->*instr.Ptr)();
				return;
		}
	}
}

void		ScriptParser::cmdName(void){
	this->mStageName = parser.extractWord();
}

void		ScriptParser::cmdRequire(void){
	this->mRessourceName = parser.extractWord();
}

void		ScriptParser::cmdAddCron(void){
	this->mAddCronFrame = parser.extractValue<int>();
	this->mAddCronTimer = parser.extractValue<int>();
	this->mAddCronIdCron = parser.extractValue<int>();
	this->mAddCronFireMob = parser.extractWord();
	this->mAddCronIdMonster = parser.extractValue<int>();
	this->mAddCronAngle = parser.extractValue<int>();
}

void		ScriptParser::cmdRemoveCron(void){
	this->mRemoveCronFrame = parser.extractValue<int>();
	this->mRemoveCronIdCron = parser.extractValue<int>();
}

void		ScriptParser::cmdAction(void){
/*	CommandAction c;

	c.setFrame(extractValue)*/

	std::string	wordContent;
	this->mActionFrame = parser.extractValue<int>();
	this->mActionMobAction = parser.extractWord();

	for (const auto &instr : MonsterCmdTab)
	if (instr.mobAction == this->mActionMobAction) {
		(this->*instr.ftPtr)();
		return;
	}
}

void		ScriptParser::fctSpawnMob(void){
	this->mSpawnIdMonster = parser.extractValue<int>();
	this->mSpawnName = parser.extractWord();
	this->mSpawnXpos = parser.extractValue<int>();
	this->mSpawnYpos = parser.extractValue<int>();
	this->mSpawnAngle = parser.extractValue<int>();
}

void		ScriptParser::fctMoveMob(void){
	this->mMoveMobIdMonster = parser.extractValue<int>();
	this->mMoveMobAngle = parser.extractValue<int>();
}

std::string		ScriptParser::getName(void) const{
	return this->mStageName;
}

std::string		ScriptParser::getRequire(void) const{
	return this->mRessourceName;
}

int				ScriptParser::getActionFrame(void) const{
	return this->mActionFrame;
}

std::string		ScriptParser::getActionMobAction(void) const{
	return this->mActionMobAction;
}

std::string		ScriptParser::getActionSpawnName(void) const{
	return this->mSpawnName;
}

int				ScriptParser::getActionSpawnIdMonster(void) const{
	return this->mSpawnIdMonster;
}

int				ScriptParser::getActionSpawnXpos(void) const{
	return this->mSpawnXpos;
}

int				ScriptParser::getActionSpawnYpos(void) const{
	return this->mSpawnYpos;
}

int				ScriptParser::getActionSpawnAngle(void) const{
	return this->mSpawnAngle;
}

int				ScriptParser::getActionMoveMobIdMonster(void) const{
	return this->mMoveMobIdMonster;
}

int				ScriptParser::getActionMoveMobAngle(void) const{
	return this->mMoveMobAngle;
}

int				ScriptParser::getAddCronFrame(void) const{
	return this->mAddCronFrame;
}

int				ScriptParser::getAddCronTimer(void) const{
	return this->mAddCronTimer;
}

int				ScriptParser::getAddCronIdCron(void) const{
	return this->mAddCronIdCron;
}

std::string			ScriptParser::getAddCronFireMob(void) const{
	return this->mAddCronFireMob;
}

int				ScriptParser::getAddCronIdMonster(void) const{
	return this->mAddCronIdMonster;
}

int				ScriptParser::getAddCronAngle(void) const{
	return this->mAddCronAngle;
}

int				ScriptParser::getRemoveCronFrame(void) const{
	return this->mRemoveCronFrame;
}

int				ScriptParser::getRemoveCronIdCron(void) const{
	return this->mRemoveCronIdCron;
}