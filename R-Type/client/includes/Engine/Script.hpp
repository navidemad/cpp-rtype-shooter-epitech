#pragma once

class Script
{
    // ctor - dtor
    public:
        explicit Script();
        ~Script();

    // copy operators
    public:
        Script(const Script &) = delete;
        Script(Script &&) = delete;
        const Script &operator=(const Script &) = delete;
        const Script &operator=(Script &&) = delete;
};
