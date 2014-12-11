#pragma once

#include "NoCopyable.hpp"
#include "IScriptCommand.hpp"

#include <vector>
#include <memory>
#include <cstdint>

class Script {

    // ctor / dtor
    public:
        Script(void);
        ~Script(void);
		Script(const Script &);
		const Script &operator=(const Script &);

	// internal functions
	public:
		void addAction(std::shared_ptr<IScriptCommand> command);
		const std::vector<std::shared_ptr<IScriptCommand>>& getCommands(void) const;
        const std::string& getTextScript(void) const;
        void setTextScript(const std::string&);

	// attributes
	private:
		std::vector<std::shared_ptr<IScriptCommand>> mCommands;
        std::string mTextScript;
};
