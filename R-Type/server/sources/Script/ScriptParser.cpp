#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "ScriptParser.hpp"

ScriptParser::ScriptParser(void) {

}

ScriptParser::~ScriptParser(void) {

}

std::string ScriptParser::extractWord(void){
	std::string	word;

	if (this->_wtab.size() == 0)
		return "";

	word = this->_wtab.front();
	this->jumpToNextToken();

	return word;
}

void		ScriptParser::parseFile(std::ifstream &file){
	std::map<std::string, void (ScriptParser::*)(const std::string&)> command;
	std::string lineContent;

	command["name"] = &ScriptParser::cmdName;
	command["action"] = &ScriptParser::cmdAction;
	command["require"] = &ScriptParser::cmdRequire;
	command["add_cron"] = &ScriptParser::cmdAddCron;
	command["remove_cron"] = &ScriptParser::cmdRemoveCron;

	while (file.good()){
		std::getline(file, lineContent);
		this->setStringToParse(lineContent);
	}
}

void		ScriptParser::cmdAction(const std::string&){

}

void		ScriptParser::cmdAddCron(const std::string&){

}

void		ScriptParser::cmdName(const std::string&){

}

void		ScriptParser::cmdRemoveCron(const std::string&){

}

void		ScriptParser::cmdRequire(const std::string&){

}

void		ScriptParser::getActions(const std::string& actionName){

}

void		ScriptParser::getName(const std::string& name){

}

void ScriptParser::jumpToNextToken(void){
	if (this->_wtab.size())
		this->_wtab.pop_front();
}

void ScriptParser::setStringToParse(const std::string &str){
	this->_str = str;
	this->splitString();
}

void ScriptParser::setTokenSep(char tokenSep){
	this->_tokenSep = tokenSep;
}

void ScriptParser::splitString(void){
	std::string substr;
	size_t		pos = -1;
	size_t		end_substr;

	this->_wtab.clear();

	do {
		++pos;
		end_substr = this->_str.find(this->_tokenSep, pos + 1);
		end_substr = end_substr == std::string::npos ? this->_str.length() : end_substr;

		substr = this->_str.substr(pos, end_substr - pos);

		if (substr != "")
			this->_wtab.push_back(substr);
	} while ((pos = this->_str.find(this->_tokenSep, pos)) != std::string::npos);
}