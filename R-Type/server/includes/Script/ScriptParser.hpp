#pragma once

#include "Parser.hpp"
#include "NoCopyable.hpp"
#include "IScriptCommand.hpp"
#include "Script.hpp"

#include <vector>
#include <memory>

class ScriptParser : public NoCopyable {

	// ctor / dtor
	public:
		ScriptParser(void) = default;
		~ScriptParser(void) = default;

	// internal functions
	public:
        std::shared_ptr<NGame::Script> createScriptFromFile(std::ifstream &);

    // workflow commands
    private:
        const IScriptCommand* commandScriptSpawn(void);

    // attributes
	private:
		Parser mParser;

	private:
		struct tokenExec {
			std::string cmd;
			const IScriptCommand* (ScriptParser::*Ptr)();
		};
		static const ScriptParser::tokenExec tokenExecTab[];

};
