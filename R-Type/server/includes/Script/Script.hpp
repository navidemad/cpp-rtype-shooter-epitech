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
            explicit Script(const std::vector<const IScriptCommand*>& commands);
            ~Script(void);
            Script(const Script& rhs);
            const Script& operator=(const Script& rhs);
            void deepCopy(const NGame::Script& rhs);

        // getters
        public:
            const std::vector<const IScriptCommand*>& getCommands(void) const;

        // workflow script
        public:
            const IScriptCommand* currentCommand(void) const;
            bool isFinish(void) const;
            void goToNextCommand(void);

        // attributes
        private:
            std::vector<const IScriptCommand*> mCommands;
            unsigned int mSize;
            unsigned int mIndex;
    };

}