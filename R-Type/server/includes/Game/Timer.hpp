#pragma once

#include "NoCopyable.hpp"

#include <chrono>
#include <ctime>

class Timer : public NoCopyable {

    // ctor / dtor
    public:
        Timer(void);
        ~Timer(void);

    // internal functions
    public:
        void reset(void);
		double frame() const;

    // attributes
    private:
        std::clock_t mStartTime;
};
