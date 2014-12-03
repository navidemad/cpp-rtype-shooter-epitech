#include <fstream>
#include <list>
#include <iostream>
#include "ScriptException.hpp"
#include "ScriptParser.hpp"
#include "ScriptLoader.hpp"
#include "PortabilityBuilder.hpp"

ScriptLoader::ScriptLoader(void) : mReaddir(PortabilityBuilder::getReaddir()) {
}

ScriptLoader::~ScriptLoader(void) {
}

std::shared_ptr<Script> ScriptLoader::loadScript(const std::string& stage_name) {
	return mScripts[stage_name];
}

void ScriptLoader::loadAll(void) {
	ScriptParser Parser;
	const std::string& pathFolder = "../shared/scripts";
	auto files = mReaddir->readFolder(pathFolder);
	for (const auto& file : files)
	{
		std::ifstream fs(pathFolder + "/" + file);
		if (!fs.good() || fs.fail())
			throw ScriptException("impossible d'ouvrir le fichier");
		else
		{
			try
			{
				mScripts[file] = Parser.parseFile(fs);
				std::cout << mScripts[file]->getTextScript();
			}
			catch (const std::exception& e){
				Utils::logError(e.what());
			}
		}
	}
}

const std::map<std::string, std::shared_ptr<Script>>& ScriptLoader::getScripts() const {
    return mScripts;
}