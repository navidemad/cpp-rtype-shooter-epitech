#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <iostream>
#include <vector>

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
		{
			std::cout << "bad cast on '" << str << "'" << std::endl;
			throw std::bad_cast();
		}
		return val;
	}

    void logInfo(const std::string &log);
    void logError(const std::string &log);
	std::string basename(const std::string &);
	std::string removeExtension(const std::string &pathname);
	std::vector<std::string> split(const std::string& str, int delimiter(int) = ::isspace);
	int iseol(int ch);
	
	#if defined(__OS_LINUX__)
		const std::string YELLOW = "\033[1;33m";
		const std::string WHITE = "\033[0;37m";
		const std::string RED = "\033[1;31m";
		struct MatchPathSeparator {
			bool operator()(char ch) const {
				return ch == '\\' || ch == '/';
			}
		};
	#elif defined(__OS_WINDOWS__)
		const std::string YELLOW = "";
		const std::string WHITE = "";
		const std::string RED = "";
		struct MatchPathSeparator {
			bool operator()(char ch) const {
				return ch == '/';
			}
		};
	#endif

}
