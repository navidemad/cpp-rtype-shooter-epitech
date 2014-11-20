#pragma once

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
#endif
