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
		short				getAddCronAngle(void) const { return mAddCronAngle; }

		void				setAddCronFrame(double frame) { mAddCronFrame = frame; }
		void				setAddCronTimer(double timer) { mAddCronTimer = timer; }
		void				setAddCronIdCron(int idCron) { mAddCronIdCron = idCron; }
		void				setAddCronFireMob(const std::string& fireMob) { mAddCronFireMob = fireMob; }
		void				setAddCronIdMonster(int idMonster) { mAddCronIdMonster = idMonster; }
		void				setAddCronAngle(short angle) { mAddCronAngle = angle; }

	// attribut
	public:
		double					mAddCronFrame;
		double					mAddCronTimer;
		int						mAddCronIdCron;
		std::string				mAddCronFireMob;
		int						mAddCronIdMonster;
		short					mAddCronAngle;

    // overload << display
    public:
        friend std::ostream&                operator << (std::ostream& os, std::shared_ptr<ScriptAddCron> rhs) {
            os <<
                "[ScriptAddCron] [Frame #" << rhs->getFrame() << "]" << std::endl <<
                "  - mAddCronFrame: '" << rhs->getAddCronFrame() << std::endl << 
                "  - mAddCronTimer: '" << rhs->getAddCronTimer() << std::endl <<
                "  - mAddCronIdCron: '" << rhs->getAddCronIdCron() << std::endl <<
                "  - mAddCronFireMob: '" << rhs->getAddCronFireMob() << std::endl <<
                "  - mAddCronIdMonster: '" << rhs->getAddCronIdMonster() << std::endl <<
                "  - mAddCronAngle: '" << rhs->getAddCronAngle() << std::endl;
            return os;
        }
};