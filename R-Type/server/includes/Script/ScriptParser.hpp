#pragma once

#include <list>
#include "Parser.hpp"
#include "Utils.hpp"
#include "NoCopyable.hpp"

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
		std::string		getName(void) const;
		std::string		getRequire(void) const;
		int				getActionFrame(void) const;
		std::string		getActionMobAction(void) const;
		int				getActionSpawnIdMonster(void) const;
		std::string		getActionSpawnName(void) const;
		int				getActionSpawnXpos(void) const;
		int				getActionSpawnYpos(void) const;
		int				getActionSpawnAngle(void) const;
		int				getActionMoveMobIdMonster(void) const;
		int				getActionMoveMobAngle(void) const;
		int				getAddCronFrame(void) const;
		int				getAddCronTimer(void) const;
		int				getAddCronIdCron(void) const;
		std::string		getAddCronFireMob(void) const;
		int				getAddCronIdMonster(void) const;
		int				getAddCronAngle(void) const;
		int				getRemoveCronFrame(void) const;
		int				getRemoveCronIdCron(void) const;
		void			parseFile(std::ifstream &);
		void			cmdName(void);
		void			cmdRequire(void);
		void			cmdAction(void);
		void			cmdAddCron(void);
		void			cmdRemoveCron(void);
		void			fctSpawnMob(void);
		void			fctMoveMob(void);

	private:
		std::string				mStageName;
		std::string				mRessourceName;
		int						mActionFrame;
		std::string				mActionMobAction;
		int						mAddCronFrame;
		int						mAddCronTimer;
		int						mAddCronIdCron;
		std::string				mAddCronFireMob;
		int						mAddCronIdMonster;
		int						mAddCronAngle;
		int						mRemoveCronFrame;
		int						mRemoveCronIdCron;
		int						mSpawnIdMonster;
		std::string				mSpawnName;
		int						mSpawnXpos;
		int						mSpawnYpos;
		int						mSpawnAngle;
		int						mMoveMobIdMonster;
		int						mMoveMobAngle;
		Parser					parser;

	private:
		void						splitString(void);

	private:
		struct tokenExec {
			std::string		cmd;
			void			(ScriptParser::*Ptr)();
		};
	static const ScriptParser::tokenExec tokenExecTab[];

	private:
		struct MonsterCmd {
			std::string		mobAction;
			void			(ScriptParser::*ftPtr)(void);
		};
		static const ScriptParser::MonsterCmd MonsterCmdTab[];
	};
