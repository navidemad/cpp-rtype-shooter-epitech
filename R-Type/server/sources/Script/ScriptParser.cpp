#include <iostream>
#include <string>
#include <fstream>
#include <map>
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

std::string ScriptParser::extractWord(void){
	std::string	word;

	if (this->mWtab.size() == 0)
		return "";

	word = this->mWtab.front();
	this->jumpToNextToken();

	return word;
}

void		ScriptParser::parseFile(std::ifstream &file){
	std::string lineContent;
	std::string wordContent;

	while (file.good()){
		std::getline(file, lineContent);
		this->setStringToParse(lineContent);
		wordContent = this->extractWord();
		std::cout << "LineContent = " << lineContent << std::endl;
		std::cout << "premier mot : " << wordContent << std::endl;

		for (const auto &instr : tokenExecTab)
			if (instr.cmd == wordContent) {
				(this->*instr.Ptr)(this->mStr);
				return;
		}
	}
}

void		ScriptParser::cmdName(const std::string&){
	this->mStageName = this->extractWord();
}

void		ScriptParser::cmdRequire(const std::string&){
	this->mRessourceName = this->extractWord();
}

void		ScriptParser::cmdAddCron(const std::string&){
	this->mAddCronFrame = extractValue<int>();
	this->mAddCronTimer = extractValue<int>();
	this->mAddCronIdCron = extractValue<int>();
	this->mAddCronFireMob = this->extractWord();
	this->mAddCronIdMonster = extractValue<int>();
	this->mAddCronAngle = extractValue<int>();
}

void		ScriptParser::cmdRemoveCron(const std::string&){
	this->mRemoveCronFrame = extractValue<int>();
	this->mRemoveCronIdCron = extractValue<int>();
}

void		ScriptParser::cmdAction(const std::string&){
/*	CommandAction c;

	c.setFrame(extractValue)*/

	std::string	wordContent;
	this->mActionFrame = extractValue<int>();
	this->mActionMobAction = this->extractWord();

	for (const auto &instr : MonsterCmdTab)
	if (instr.mobAction == this->mActionMobAction) {
		(this->*instr.ftPtr)(this->mStr);
		return;
	}
}

void		ScriptParser::fctSpawnMob(const std::string&){
	this->mSpawnIdMonster = extractValue<int>();
	this->mSpawnName = this->extractWord();
	this->mSpawnXpos = extractValue<int>();
	this->mSpawnYpos = extractValue<int>();
	this->mSpawnAngle = extractValue<int>();
}

void		ScriptParser::fctMoveMob(const std::string&){
	this->mMoveMobIdMonster = extractValue<int>();
	this->mMoveMobAngle = extractValue<int>();
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

void ScriptParser::jumpToNextToken(void){
	if (this->mWtab.size())
		this->mWtab.pop_front();
}

void ScriptParser::setStringToParse(const std::string &str){
	this->mStr = str;
	this->splitString();
}

void ScriptParser::setTokenSep(char tokenSep){
	this->mTokenSep = tokenSep;
}

void ScriptParser::splitString(void){
	std::string substr;
	size_t		pos = -1;
	size_t		end_substr;

	this->mWtab.clear();

	do {
		++pos;
		end_substr = this->mStr.find(this->mTokenSep, pos + 1);
		end_substr = end_substr == std::string::npos ? this->mStr.length() : end_substr;

		substr = this->mStr.substr(pos, end_substr - pos);

		if (substr != "")
			this->mWtab.push_back(substr);
	} while ((pos = this->mStr.find(this->mTokenSep, pos)) != std::string::npos);
}