#pragma once

class Collision
{
    // ctor - dtor
    public:
        explicit Collision();
        ~Collision();

    // copy operators
    public:
        Collision(const Collision &) = delete;
        Collision(Collision &&) = delete;
        const Collision &operator=(const Collision &) = delete;
        const Collision &operator=(Collision &&) = delete;
};
