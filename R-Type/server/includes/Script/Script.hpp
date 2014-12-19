#pragma once

#include "AScriptCommand.hpp"

#include <vector>
#include <cstdint>

class Script {

    // ctor / dtor
    public:
		Script(void) = default;
        ~Script(void) = default;
		Script(const Script &);
		const Script &operator=(const Script &);

	// getters
	public:
		void setCommands(const std::vector<AScriptCommand>&);
		const std::vector<AScriptCommand>& getCommands(void) const;

	// workflow script
	public:
		const AScriptCommand& currentAction(void) const;
		bool goToNextAction(void);

	// attributes
	private:
		std::vector<AScriptCommand>::const_iterator mCurrentIterator;
		std::vector<AScriptCommand> mCommands;
};
