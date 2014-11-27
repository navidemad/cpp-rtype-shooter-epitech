#pragma once

#include "NoCopyable.hpp"

#include <chrono>
#include <ctime>

class Timer : public NoCopyable {

    // ctor / dtor
    public:
        explicit Timer(void);
        ~Timer(void);

    // internal functions
    public:
        void restart();
        double frame() const;

    // attributes
    private:
        std::clock_t mStart;
};
