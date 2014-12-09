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
		explicit ScriptParser(void);
		~ScriptParser(void);

	// copy / move operators
	public:
		ScriptParser(const ScriptParser &) = delete;
		ScriptParser(const ScriptParser &&) = delete;
		const ScriptParser &operator=(const ScriptParser &&) = delete;
		const ScriptParser &operator=(const ScriptParser &) = delete;

	// internal functions
	public:
		std::shared_ptr<Script>			parseFile(std::ifstream &);
		const std::string&				getName(void) const;
		const std::string&				getRequire(void) const;
		double							getActionFrame(void) const;
		const std::string&				getActionMobAction(void) const;
		int								getActionSpawnIdMonster(void) const;
		const std::string&				getActionSpawnName(void) const;
		double							getActionSpawnXpos(void) const;
		double							getActionSpawnYpos(void) const;
		double							getActionSpawnAngle(void) const;
		int								getActionMoveMobIdMonster(void) const;
		double							getActionMoveMobAngle(void) const;
		int								getAddCronFrame(void) const;
		double							getAddCronTimer(void) const;
		int								getAddCronIdCron(void) const;
		std::string						getAddCronFireMob(void) const;
		int								getAddCronIdMonster(void) const;
		double							getAddCronAngle(void) const;
		double							getRemoveCronFrame(void) const;
		int								getRemoveCronIdCron(void) const;
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
