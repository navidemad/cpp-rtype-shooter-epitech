#pragma once

#include "NoCopyable.hpp"
#include "IScriptCommand.hpp"

#include <vector>
#include <memory>
#include <cstdint>

class Script : public NoCopyable {

    // ctor / dtor
    public:
        explicit Script(void);
        ~Script(void);

	// internal functions
	public:
		void addAction(std::shared_ptr<IScriptCommand> command);
		std::shared_ptr<IScriptCommand> currentAction(void) const;
		std::vector<std::shared_ptr<IScriptCommand>> getCommands(void) const;
		void restart(void);
		bool goToNextAction(void);
		bool goToPrevAction(void);

	// attributes
	private:
		std::vector<std::shared_ptr<IScriptCommand>> mCommands;
		uint32_t mIndex;
};
