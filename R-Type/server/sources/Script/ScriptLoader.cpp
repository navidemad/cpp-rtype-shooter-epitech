#include <fstream>
#include <list>
#include <iostream>
#include "ScriptException.hpp"
#include "ScriptParser.hpp"
#include "ScriptLoader.hpp"

ScriptLoader::ScriptLoader(void) {
}

ScriptLoader::~ScriptLoader(void) {
}

void ScriptLoader::loadScript(const std::string& path) {
	ScriptParser Parser;
	std::ifstream file;

	if (!file.good() || file.fail())
		throw ScriptException("impossible d'ouvrir le fichier");
	else{
		file.open(path);
		Parser.parseFile(file);
	}
}

void ScriptLoader::loadAll(void){

}

/*
std::shared_ptr<Script> ScriptLoader::loadScript(const std::string& stage_name) {
	return mScripts[Stage_name];
}

void ScriptLoader::loadAll(void) {
	ScriptParser parser;
	std::ifstream file;

	if (!file.good() || file.fail())
		throw ScriptException("impossible d'ouvrir le fichier");

	file.open(path);
	mScripts[filename] = parser.parseFile(file); // parseFile retourne un std::shared_ptr<Script>
}
*/