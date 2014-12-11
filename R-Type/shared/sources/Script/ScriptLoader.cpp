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

const Script& ScriptLoader::getScript(const std::string& stage_name) const {
	if (mScripts.count(stage_name) == 0)
	{
		std::cerr << "mScripts[" << stage_name << "] n'existe pas" << std::endl;
		std::cerr << "Voici les stage_name disponibles:" << std::endl;
		for (const auto &p : mScripts)
			std::cout << "mScripts[" << p.first << "]" << std::endl;
	}
	return mScripts.at(stage_name);
}

void ScriptLoader::loadAll(void) {
	Utils::logInfo("Loading scripts:");
	ScriptParser Parser;

	const std::string& pathFolder = "./files";
	auto files = mReaddir->readFolder(pathFolder);

	for (const auto& pathFile : files)
	{
		std::ifstream fs(pathFile);

		std::stringstream ss;
		ss << Utils::RED << "[SCRIPT]" << Utils::YELLOW << "[" << pathFile << "]> " << Utils::WHITE;

		if (!fs.good() || fs.fail())
		{
			ss << "impossible d'ouvrir le fichier";
			Utils::logError(ss.str());
		}
		else
		{
			try
			{
				mScripts[Utils::removeExtension(Utils::basename(pathFile))] = Parser.parseFile(fs);
				ss << "done";
				Utils::logInfo(ss.str());
			}
			catch (const std::exception& e){
				ss << e.what();
				Utils::logError(ss.str());
			}
		}
	}
}

const std::map<std::string, Script>& ScriptLoader::getScripts() const {
    return mScripts;
}