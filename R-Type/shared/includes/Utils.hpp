#pragma once

#include <string>
#include <memory>

namespace Utils
{
    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique(Args&& ...args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
    void logInfo(const std::string &log);
    void logError(const std::string &log);
}
