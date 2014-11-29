#pragma once

#include <string>
#include "IScriptCommand.hpp"

class ScriptName : public IScriptCommand {
	// virtual destructor
	public:
		explicit ScriptName(void) { }
		~ScriptName(void) { }

	// public pure methods
	public:
		virtual IScriptCommand::Instruction	getInstruction(void) const { return IScriptCommand::Instruction::NAME; }

	// getter-setter
	public:
		std::string				getName(void) const { return mStageName; }

		void					setName(const std::string &name) { mStageName = name; }

	// attribut
	public:
		std::string				mStageName;
};