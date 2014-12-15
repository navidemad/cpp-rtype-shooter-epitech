#pragma once

#include <string>
#include "IScriptCommand.hpp"

class ScriptRequire : public IScriptCommand {
	// virtual destructor
	public:
		ScriptRequire(void) = default;
		~ScriptRequire(void) = default;

	// public pure methods
	public:
		virtual IScriptCommand::Instruction	getInstruction(void) const { return IScriptCommand::Instruction::REQUIRE; }
		virtual double						getFrame(void) const { return 0.0; }

	// getter-setter
	public:
		std::string				getRessourceName(void) const { return mRessourceName; }
		void					setRessourceName(const std::string &name) { mRessourceName = name; }

	// attribut
	public:
		std::string				mRessourceName;

    // overload << display
    public:
        friend std::ostream&                operator << (std::ostream& os, std::shared_ptr<ScriptRequire> rhs) {
            os <<
                "[ScriptRequire] [Frame #" << rhs->getFrame() << "]" << std::endl <<
                "  - mRessourceName: '" << rhs->getRessourceName() << std::endl;
            return os;
        }
};