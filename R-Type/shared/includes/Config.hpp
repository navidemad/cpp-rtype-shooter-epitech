#pragma once

/*
** Detect OS
*/
#if (defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__)) && (!defined(__unix__) && !defined(__unix) && !defined(unix))
# define __OS_WINDOWS__
# include <WinSock2.h>
# include <Windows.h>
# include <time.h>
#elif (defined(__unix__) || defined(__unix) || defined(unix)) && (!defined(_WIN32) && !defined(WIN32) && !defined(__WINDOWS__))
# define __OS_LINUX__
# include <sys/select.h>
# include <sys/types.h>
# include <sys/time.h>
# include <unistd.h>
# include <cstdint>
#else
# error "[WINDOWS - LINUX] Only. Your OS is not supported"
#endif

/*
** it will be implemented on C++14
** http://herbsutter.com/gotw/_102/
*/
#include <memory>
namespace Utils
{
    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique(Args&& ...args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
