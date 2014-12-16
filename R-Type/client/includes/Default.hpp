#pragma once

#include <string>

namespace Config
{
	namespace Window
	{
		const std::string	nameWindow = "R-Type Project";

		const unsigned int	x = 1920;
		const unsigned int	y = 1080;
	}

	namespace Game
	{
		const std::string	defaultNameGame = "Simon suce des ours";
		const std::string	defaultLevelGame = "stage_1";
	}

	namespace Network
	{
		const unsigned int	port = 4249;
		const std::string	adress = "localhost";
		const std::string	defaultPseudo = "anon en mousse";
	}
}