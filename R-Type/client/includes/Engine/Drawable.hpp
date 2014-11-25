#pragma once

class Drawable
{
    // ctor - dtor
    public:
        explicit Drawable();
        ~Drawable();

    // copy operators
    public:
        Drawable(const Drawable &) = delete;
        Drawable(Drawable &&) = delete;
        const Drawable &operator=(const Drawable &) = delete;
        const Drawable &operator=(Drawable &&) = delete;
};
