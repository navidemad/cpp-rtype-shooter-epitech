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

void ScriptLoader::loadAll(void) {
	std::string path;
}