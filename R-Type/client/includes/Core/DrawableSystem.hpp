#pragma once

#include "../Engine/System.hpp"

class DrawableSystem
{
    // ctor - dtor
    public:
        explicit DrawableSystem();
        ~DrawableSystem();

    // copy operators
    public:
        DrawableSystem(const DrawableSystem &) = delete;
        DrawableSystem(DrawableSystem &&) = delete;
        const DrawableSystem &operator=(const DrawableSystem &) = delete;
        const DrawableSystem &operator=(DrawableSystem &&) = delete;
};
