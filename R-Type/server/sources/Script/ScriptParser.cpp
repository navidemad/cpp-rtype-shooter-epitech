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
		Parser.setStringToParse(lineContent);
		wordContent = Parser.extractWord();
		std::cout << "premier mot : " << wordContent << std::endl;

		for (const auto &instr : tokenExecTab)
			if (instr.cmd == wordContent) {
				(this->*instr.Ptr)();
				return;
		}
	}
}

void		ScriptParser::cmdName(void){
	this->mStageName = Parser.extractWord();
}

void		ScriptParser::cmdRequire(void){
	this->mRessourceName = Parser.extractWord();
}

void		ScriptParser::cmdAddCron(void){
	this->mAddCronFrame = Parser.extractValue<int>();
	this->mAddCronTimer = Parser.extractValue<int>();
	this->mAddCronIdCron = Parser.extractValue<int>();
	this->mAddCronFireMob = Parser.extractWord();
	this->mAddCronIdMonster = Parser.extractValue<int>();
	this->mAddCronAngle = Parser.extractValue<int>();
}

void		ScriptParser::cmdRemoveCron(void){
	this->mRemoveCronFrame = Parser.extractValue<int>();
	this->mRemoveCronIdCron = Parser.extractValue<int>();
}

void		ScriptParser::cmdAction(void){
/*	CommandAction c;

	c.setFrame(extractValue)*/

	std::string	wordContent;
	this->mActionFrame = Parser.extractValue<int>();
	this->mActionMobAction = Parser.extractWord();

	for (const auto &instr : MonsterCmdTab)
	if (instr.mobAction == this->mActionMobAction) {
		(this->*instr.ftPtr)();
		return;
	}
}

void		ScriptParser::fctSpawnMob(void){
	this->mSpawnIdMonster = Parser.extractValue<int>();
	this->mSpawnName = Parser.extractWord();
	this->mSpawnXpos = Parser.extractValue<int>();
	this->mSpawnYpos = Parser.extractValue<int>();
	this->mSpawnAngle = Parser.extractValue<int>();
}

void		ScriptParser::fctMoveMob(void){
	this->mMoveMobIdMonster = Parser.extractValue<int>();
	this->mMoveMobAngle = Parser.extractValue<int>();
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