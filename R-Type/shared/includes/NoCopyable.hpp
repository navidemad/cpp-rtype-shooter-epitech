#pragma once

class NoCopyable {

public:
    NoCopyable() = default;
    ~NoCopyable() = default;
    NoCopyable(const NoCopyable &) = delete;
    NoCopyable(NoCopyable &&) = delete;
    const NoCopyable &operator=(const NoCopyable &) = delete;
    const NoCopyable &operator=(NoCopyable &&) = delete;

};
