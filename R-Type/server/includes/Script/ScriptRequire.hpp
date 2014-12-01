#pragma once

#include <string>
#include "IScriptCommand.hpp"

class ScriptRequire : public IScriptCommand {
	// virtual destructor
	public:
		explicit ScriptRequire(void) { }
		~ScriptRequire(void) { }

	// public pure methods
	public:
		virtual IScriptCommand::Instruction	getInstruction(void) const { return IScriptCommand::Instruction::REQUIRE; }

	// getter-setter
	public:
		std::string				getRessourceName(void) const { return mRessourceName; }

		void					setRessourceName(const std::string &name) { mRessourceName = name; }

	// attribut
	public:
		std::string				mRessourceName;
};