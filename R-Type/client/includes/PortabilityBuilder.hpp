#pragma once

#include "Config.hpp"

#if defined(__OS_LINUX__)
# include "UnixPortabilityBuilder.hpp"
#elif defined(__OS_WINDOWS__)
# include "WindowsPortabilityBuilder.hpp"
#endif
