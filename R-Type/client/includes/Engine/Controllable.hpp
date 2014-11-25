#pragma once

class Controllable
{
    // ctor - dtor
    public:
        explicit Controllable();
        ~Controllable();

    // copy operators
    public:
        Controllable(const Controllable &) = delete;
        Controllable(Controllable &&) = delete;
        const Controllable &operator=(const Controllable &) = delete;
        const Controllable &operator=(Controllable &&) = delete;
};
