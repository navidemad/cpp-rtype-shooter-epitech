#pragma once

#include <string>
#include "IScriptCommand.hpp"

class ScriptRemoveCron : public IScriptCommand {
	// virtual destructor
	public:
		explicit ScriptRemoveCron(void) { }
		~ScriptRemoveCron(void) { }

	// public pure methods
	public:
		virtual IScriptCommand::Instruction	getInstruction(void) const { return IScriptCommand::Instruction::REMOVE_CRON; }

	// getter-setter
	public:
		int					getRemoveCronFrame(void) const { return mRemoveCronFrame; }
		int					getRemoveCronIdCron(void) const { return mRemoveCronIdCron; }

		void				setRemoveCronFrame(const int& frame) { mRemoveCronFrame = frame; }
		void				setRemoveCronIdCron(const int& idCron) { mRemoveCronIdCron = idCron; }

	// attribut
	public:
		int					mRemoveCronFrame;
		int					mRemoveCronIdCron;
};