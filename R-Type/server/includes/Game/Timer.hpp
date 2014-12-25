#pragma once

#include "NoCopyable.hpp"

#include <chrono>

namespace NGame {

    class Timer : public NoCopyable {

        // ctor / dtor
        public:
            Timer(void);
            ~Timer(void) = default;

        // internal functions
        public:
            long long getDelta(void) const;
            void restart(void);

        // attributes
        private:
            std::chrono::system_clock::time_point mLast;

    };

}