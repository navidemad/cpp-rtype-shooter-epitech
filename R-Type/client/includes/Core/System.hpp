#pragma once

class System
{
    // ctor - dtor
    public:
        explicit System();
        ~System();

    // copy operators
    public:
        System(const System &) = delete;
        System(System &&) = delete;
        const System &operator=(const System &) = delete;
        const System &operator=(System &&) = delete;
};
