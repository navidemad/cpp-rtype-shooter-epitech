#pragma once

#include <string>

class ScriptLoader {

    // ctor / dtor
    public:
        explicit ScriptLoader(void);
        ~ScriptLoader(void);

    // copy / move operators
    public:
        ScriptLoader(const ScriptLoader &) = delete;
        ScriptLoader(const ScriptLoader &&) = delete;
        const ScriptLoader &operator=(const ScriptLoader &) = delete;
        const ScriptLoader &operator=(const ScriptLoader &&) = delete;

    // internal functions
    public:
        void loadScript(const std::string&);
        void loadAll(void);

};
