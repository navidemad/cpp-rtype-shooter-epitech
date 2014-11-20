#pragma once

#if defined(__OS_WINDOWS__)
# include <WinSock2.h>
# include <Windows.h>
# include <time.h>
#elif defined(__OS_LINUX__)
# include <sys/select.h>
# include <sys/types.h>
# include <sys/time.h>
# include <unistd.h>
# include <cstdint>
#endif
