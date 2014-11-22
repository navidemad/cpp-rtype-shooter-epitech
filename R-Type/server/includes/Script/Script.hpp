#pragma once

class Script {

    // ctor / dtor
    public:
        explicit Script(void);
        ~Script(void);

    // copy / move operators
    public:
        Script(const Script &) = delete;
        Script(const Script &&) = delete;
        const Script &operator=(const Script &) = delete;
        const Script &operator=(const Script &&) = delete;

};
