#pragma once

#include <string>
#include "IScriptCommand.hpp"

class ScriptAddCron : public IScriptCommand {
	// virtual destructor
	public:
		ScriptAddCron(void) = default;
		~ScriptAddCron(void) = default;

	// public pure methods
	public:
		virtual IScriptCommand::Instruction	getInstruction(void) const { return IScriptCommand::Instruction::ADD_CRON; }
		virtual double						getFrame(void) const { return this->mAddCronFrame; }

	// getter-setter
	public:
		double				getAddCronFrame(void) const { return mAddCronFrame; }
		double				getAddCronTimer(void) const { return mAddCronTimer; }
		int					getAddCronIdCron(void) const { return mAddCronIdCron; }
		std::string			getAddCronFireMob(void) const { return mAddCronFireMob; }
		int					getAddCronIdMonster(void) const { return mAddCronIdMonster; }
		double				getAddCronAngle(void) const { return mAddCronAngle; }

		void				setAddCronFrame(double frame) { mAddCronFrame = frame; }
		void				setAddCronTimer(double timer) { mAddCronTimer = timer; }
		void				setAddCronIdCron(int idCron) { mAddCronIdCron = idCron; }
		void				setAddCronFireMob(const std::string& fireMob) { mAddCronFireMob = fireMob; }
		void				setAddCronIdMonster(int idMonster) { mAddCronIdMonster = idMonster; }
		void				setAddCronAngle(double angle) { mAddCronAngle = angle; }

	// attribut
	public:
		double					mAddCronFrame;
		double					mAddCronTimer;
		int						mAddCronIdCron;
		std::string				mAddCronFireMob;
		int						mAddCronIdMonster;
		double					mAddCronAngle;
};