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

	// getters
	public:
		size_t getIndex(void) const;
		bool end(void) const;
		const std::vector<std::shared_ptr<IScriptCommand>>& getCommands(void) const;
		const std::string& getTextScript(void) const;

	// setters
	public:
		void setTextScript(const std::string&);

	// adding
	public:
		const Script &operator<<(std::shared_ptr<IScriptCommand> command); 

	// workflow script
	public:
		std::shared_ptr<IScriptCommand> currentAction(void) const;
		bool goToNextAction(void);
		bool goToPrevAction(void);

	// attributes
	private:
		size_t mIndex;
		std::vector<std::shared_ptr<IScriptCommand>> mCommands;
        std::string mTextScript;
};
