#pragma once

#include <chrono>
#include <ctime>

class Timer {

    // ctor / dtor
    public:
        explicit Timer(void);
        ~Timer(void);

    // copy / move operators
    public:
        Timer(const Timer &) = delete;
        Timer(const Timer &&) = delete;
        const Timer &operator=(const Timer &) = delete;
        const Timer &operator=(const Timer &&) = delete;

    // internal functions
    public:
        void restart();
        double frame() const;

    // attributes
    private:
        std::clock_t mStart;
};
