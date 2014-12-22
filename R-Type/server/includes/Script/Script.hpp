#pragma once

#include "IScriptCommand.hpp"

#include <vector>
#include <cstdint>
#include <memory>
#include "NoCopyable.hpp"

class Script : public NoCopyable {

    // ctor / dtor
    public:
        Script(void) = default;
        virtual ~Script(void);

	// getters
	public:
        Script& operator=(const std::vector<const IScriptCommand*>&);
		const std::vector<const IScriptCommand*>& getCommands(void) const;
        

	// workflow script
	public:
        bool last(unsigned int) const;
		const IScriptCommand* get(unsigned int) const;
        unsigned int size(void) const;

	// attributes
	private:
		std::vector<const IScriptCommand*> mCommands;
        unsigned int mSize;
};
