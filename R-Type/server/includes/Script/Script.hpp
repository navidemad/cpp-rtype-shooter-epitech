#pragma once

#include "AScriptCommand.hpp"

#include <vector>
#include <cstdint>

class Script {

    // ctor / dtor
    public:
		Script(void);
        ~Script(void) = default;
		Script(const Script &);
		const Script &operator=(const Script &);

	// getters
	public:
		void setCommands(const std::vector<AScriptCommand>&);
		const std::vector<AScriptCommand>& getCommands(void) const;

	// workflow script
	public:
		bool isFinish(void) const;
		const AScriptCommand& currentCommand(void) const;
		void goToNextCommand(void);

	// attributes
	private:
		uint64_t mIndex;
		std::vector<AScriptCommand> mCommands;
};
