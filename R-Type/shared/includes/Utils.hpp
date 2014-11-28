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

	template <typename T>
	T getNbr(const std::string &str){
		std::stringstream	ss(str);
		float				val;

		ss >> val;
		return val;
	}

    void logInfo(const std::string &log);
    void logError(const std::string &log);
}
