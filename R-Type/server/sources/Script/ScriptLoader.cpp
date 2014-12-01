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

std::shared_ptr<Script> ScriptLoader::loadScript(const std::string& stage_name) {
	return mScripts[stage_name];
}

void ScriptLoader::loadAll(void) {
	ScriptParser Parser;
	std::ifstream file;

	if (!file.good() || file.fail())
		throw ScriptException("impossible d'ouvrir le fichier");
	else{
		const std::string& path = "./sources/Script/Simon.txt";
		file.open(path);
		mScripts["Simon"] = Parser.parseFile(file);
		auto commands = mScripts["Simon"]->getCommands();
		for (const auto& command : commands)
		{
			std::cout << (int)command->getInstruction() << std::endl;
		}
	}
}