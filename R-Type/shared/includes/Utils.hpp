#pragma once

#include <string>
#include <sstream>
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
		T				val;

		if ((ss >> val).fail() || !(ss >> std::ws).eof())
			throw std::bad_cast();
		return val;
	}

    void logInfo(const std::string &log);
    void logError(const std::string &log);

    const std::string YELLOW = "\e[1;33m";
    const std::string WHITE = "\e[0;37m";
    const std::string RED = "\e[1;31m";
}
