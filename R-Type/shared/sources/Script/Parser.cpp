#include <iostream>
#include "Parser.hpp"

Parser::Parser() : mTokenSep(' ')
{

}

Parser::~Parser(void) {

}

std::string Parser::extractWord(void){
	std::string	word;

	if (this->mWtab.size() == 0)
		return "";

	word = this->mWtab.front();
	this->jumpToNextToken();

	return word;
}

void Parser::jumpToNextToken(void){
	if (this->mWtab.size())
		this->mWtab.pop_front();
}

void Parser::setStringToParse(const std::string &str){
	this->mStr = str;
	this->splitString();
}

void Parser::setTokenSep(char tokenSep){
	this->mTokenSep = tokenSep;
}

void Parser::splitString(void){
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