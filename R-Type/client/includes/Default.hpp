#pragma once

#include <string>
#include <cstdint>

namespace Config
{
	namespace Window
	{
		const std::string	nameWindow = "R-Type Project";
		const bool			fullscreenMode = false;
		const bool			FPSMode = false;

		const unsigned int	x = 1920;
		const unsigned int	y = 1080;
	}

	namespace Title
	{
		const int	sizeTitleBackground = 430;
	}

	namespace Game
	{
		const std::string	defaultNameGame = "de_dust2";
		const std::string	defaultLevelGame = "stage_2";
        const int		    defaultNbPlayerMax = 4;
		const int		    defaultNbPublicMax = 4;
	}

	namespace Network
	{
		const unsigned int	port = 4249;
		const std::string	adress = "127.0.0.1";
		const std::string	defaultPseudo = "Steve";
	}

	namespace Audio
	{
		const float			volume = 50.f;
	}
}