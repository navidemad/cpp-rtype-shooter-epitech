#pragma once

class MovementSystem
{
    // ctor - dtor
    public:
        MovementSystem();
        ~MovementSystem();

    // copy operators
    public:
        MovementSystem(const MovementSystem &) = delete;
        MovementSystem(MovementSystem &&) = delete;
        const MovementSystem &operator=(const MovementSystem &) = delete;
        const MovementSystem &operator=(MovementSystem &&) = delete;
};
