#pragma once

#include <string>
#include "IScriptCommand.hpp"

class ScriptAddCron : public IScriptCommand {
	// virtual destructor
	public:
		explicit ScriptAddCron(void) { }
		~ScriptAddCron(void) { }

	// public pure methods
	public:
		virtual IScriptCommand::Instruction	getInstruction(void) const { return IScriptCommand::Instruction::ADD_CRON; }

	// getter-setter
	public:
		int					getAddCronFrame(void) const { return mAddCronFrame; }
		int					getAddCronTimer(void) const { return mAddCronTimer; }
		int					getAddCronIdCron(void) const { return mAddCronIdCron; }
		std::string			getAddCronFireMob(void) const { return mAddCronFireMob; }
		int					getAddCronIdMonster(void) const { return mAddCronIdMonster; }
		int					getAddCronAngle(void) const { return mAddCronAngle; }

		void				setAddCronFrame(const int& frame) { mAddCronFrame = frame; }
		void				setAddCronTimer(const int& timer) { mAddCronTimer = timer; }
		void				setAddCronIdCron(const int& idCron) { mAddCronIdCron = idCron; }
		void				setAddCronFireMob(const std::string& fireMob) { mAddCronFireMob = fireMob; }
		void				setAddCronIdMonster(const int& idMonster) { mAddCronIdMonster = idMonster; }
		void				setAddCronAngle(const int& angle) { mAddCronAngle = angle; }

	// attribut
	public:
		int						mAddCronFrame;
		int						mAddCronTimer;
		int						mAddCronIdCron;
		std::string				mAddCronFireMob;
		int						mAddCronIdMonster;
		int						mAddCronAngle;
};