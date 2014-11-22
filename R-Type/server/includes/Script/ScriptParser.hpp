#pragma once

class ScriptParser {

    // ctor / dtor
    public:
        explicit ScriptParser(void);
        ~ScriptParser(void);

    // copy / move operators
    public:
        ScriptParser(const ScriptParser &) = delete;
        ScriptParser(const ScriptParser &&) = delete;
        const ScriptParser &operator=(const ScriptParser &) = delete;
        const ScriptParser &operator=(const ScriptParser &&) = delete;

};
