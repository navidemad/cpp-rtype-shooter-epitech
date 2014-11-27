#pragma once

#include "NoCopyable.hpp"

#include <string>

class ScriptLoader : public NoCopyable {

    // ctor / dtor
    public:
        explicit ScriptLoader(void);
        ~ScriptLoader(void);

    // internal functions
    public:
        void loadScript(const std::string&);
        void loadAll(void);

};
