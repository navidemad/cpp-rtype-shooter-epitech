#pragma once

#include "Parser.hpp"
#include "NoCopyable.hpp"
#include "AScriptCommand.hpp"
#include <vector>

class ScriptParser : public NoCopyable {

	// ctor / dtor
	public:
		ScriptParser(void) = default;
		~ScriptParser(void) = default;

	// internal functions
	public:
		std::vector<AScriptCommand> parseFile(std::ifstream &);

    // workflow commands
    private:
        AScriptCommand commandScriptName(void);
        AScriptCommand commandScriptRequire(void);
        AScriptCommand commandScriptSpawn(void);

    // attributes
	private:
		Parser mParser;

	private:
		struct tokenExec {
			std::string cmd;
			AScriptCommand (ScriptParser::*Ptr)();
		};
		static const ScriptParser::tokenExec tokenExecTab[];

};
