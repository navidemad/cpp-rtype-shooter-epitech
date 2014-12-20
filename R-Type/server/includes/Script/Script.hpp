#pragma once

#include "IScriptCommand.hpp"

#include <vector>
#include <cstdint>

class Script {

    // ctor / dtor
    public:
		Script(void);
        ~Script(void);
		Script(const Script &);
		const Script &operator=(const Script &);

	// getters
	public:
		void setCommands(const std::vector<const IScriptCommand*>&);
		const std::vector<const IScriptCommand*>& getCommands(void) const;

	// workflow script
	public:
		bool isFinish(void) const;
		const IScriptCommand* currentCommand(void) const;
		void goToNextCommand(void);

	// attributes
	private:
		unsigned int mIndex;
		std::vector<const IScriptCommand*> mCommands;
};
