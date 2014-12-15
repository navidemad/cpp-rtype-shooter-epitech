#pragma once

#include <list>
#include "Parser.hpp"
#include "Utils.hpp"
#include "Script.hpp"
#include "NoCopyable.hpp"
#include "IScriptCommand.hpp"
#include "ScriptAction.hpp"
#include <memory>

class ScriptParser : public NoCopyable {
	// ctor / dtor
	public:
		ScriptParser(void);
		~ScriptParser(void);

	// copy / move operators
	public:
		ScriptParser(const ScriptParser &) = delete;
		ScriptParser(const ScriptParser &&) = delete;
		const ScriptParser &operator=(const ScriptParser &&) = delete;
		const ScriptParser &operator=(const ScriptParser &) = delete;

	// internal functions
	public:
		Script										parseFile(std::ifstream &);
		Script										parseMapByString(const std::string& stage_content);

		std::shared_ptr<ScriptAction::IActionType> fctSpawnMob(void);
		std::shared_ptr<ScriptAction::IActionType> fctMoveMob(void);
		std::shared_ptr<IScriptCommand>				cmdName(void);
		std::shared_ptr<IScriptCommand>				cmdRequire(void);
		std::shared_ptr<IScriptCommand>				cmdAction(void);
		std::shared_ptr<IScriptCommand>				cmdAddCron(void);
		std::shared_ptr<IScriptCommand>				cmdRemoveCron(void);

	private:
		Parser					parser;

	private:
		void						splitString(void);

	private:
		struct tokenExec {
			std::string		cmd;
			std::shared_ptr<IScriptCommand> (ScriptParser::*Ptr)();
		};
	static const ScriptParser::tokenExec tokenExecTab[];

	private:
		struct MonsterCmd {
			std::string		mobAction;
			std::shared_ptr<ScriptAction::IActionType> (ScriptParser::*ftPtr)(void);
		};
		static const ScriptParser::MonsterCmd MonsterCmdTab[];
	};
