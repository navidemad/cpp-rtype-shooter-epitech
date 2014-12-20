#include <fstream>
#include <iostream>
#include "ScriptException.hpp"
#include "ScriptParser.hpp"
#include "ScriptLoader.hpp"
#include "PortabilityBuilder.hpp"

ScriptLoader::ScriptLoader(void) : mReaddir(PortabilityBuilder::getReaddir()) { }

ScriptLoader::~ScriptLoader(void) { }

bool ScriptLoader::has(const std::string& stage_name) const {
    return mScripts.find(stage_name) != mScripts.end();
}

const std::shared_ptr<Script>& ScriptLoader::get(const std::string& stage_name) const {
    return mScripts.at(stage_name);
}

const std::map<std::string, std::shared_ptr<Script>>& ScriptLoader::getScripts() const {
    return mScripts;
}

bool ScriptLoader::loadAll(void) {
    logInfo("Loading scripts Started");

    ScriptParser parser;

    const std::string& pathFolder = "./files";
    const auto& files = mReaddir->readFolder(pathFolder);

    for (const auto& pathFile : files) {
        std::ifstream fs(pathFile);
        try {
            if (fs.good() && !fs.fail()) {
                const std::string& key = Utils::removeExtension(Utils::basename(pathFile));
                mScripts.insert(std::make_pair(key, parser.createScriptFromFile(fs)));
                logInfo(key);
            }
        }
        catch (const ScriptException&e) {
            Utils::logError(e.what());
        }
    }
    logInfo("Loading scripts: " + Utils::toString<unsigned int>(mScripts.size()) + " rows loaded");
    return true;
    return mScripts.size() > 0;
}

void ScriptLoader::logInfo(const std::string &log) const {
    std::stringstream ss;

    ss << Utils::RED << "[ScriptLoader]" << Utils::YELLOW << "[" << "]> " << Utils::WHITE << log;
    Utils::logInfo(ss.str());
}
