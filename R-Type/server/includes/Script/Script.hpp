#pragma once

#include "IScriptCommand.hpp"

#include <vector>
#include <cstdint>
#include <memory>

namespace NGame
{

    class Script {

        // ctor / dtor
    public:
        Script(const std::vector<const IScriptCommand*>& commands);
        ~Script(void);
        Script(const Script& rhs);
        Script& operator=(const Script& rhs);

        // getters
    public:
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

}