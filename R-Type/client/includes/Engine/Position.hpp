#pragma once

class Position
{
    // ctor - dtor
    public:
        explicit Position();
        ~Position();

    // copy operators
    public:
        Position(const Position &) = delete;
        Position(Position &&) = delete;
        const Position &operator=(const Position &) = delete;
        const Position &operator=(Position &&) = delete;
};
