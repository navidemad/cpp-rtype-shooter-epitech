#pragma once

#include "Parser.hpp"
#include "NoCopyable.hpp"
#include "IScriptCommand.hpp"
#include <vector>

class ScriptParser : public NoCopyable {

	// ctor / dtor
	public:
		ScriptParser(void) = default;
		~ScriptParser(void) = default;

	// internal functions
	public:
		std::vector<const IScriptCommand*> parseFile(std::ifstream &);

    // workflow commands
    private:
        const IScriptCommand* commandScriptName(void);
        const IScriptCommand* commandScriptRequire(void);
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
