#pragma once

#include <string>
#include <cstdint>
#include <map>
#include "IResource.hpp"

namespace Config
{
	namespace Window
	{
        static const short Width = 1920;
        static const short Height = 1080;
	}

	namespace Game
	{
        static const double	                            fpsLimit = 30.0;
        static const uint64_t	                        minIdComponent = 6;
        static const int                                maxPlayersInAGame = 4;
        static const int                                maxSpectatorsInAGame = 4;
        static std::map<IResource::Direction, short>    angleTab = {
            { IResource::Direction::RIGHT, 0 },
            { IResource::Direction::BOTTOM, 90 },
            { IResource::Direction::LEFT, 180 },
            { IResource::Direction::TOP, 270 }
        };
        enum class Owner                                { P1, P2, P3, P4, IA };
	}

    namespace ThreadPool
    {
        static const unsigned int                       nbThreads = 6;
    }

	namespace Network
	{
        static const int                                tcpPort = 4249;
        static const int                                tcpQueue = 1024;
        static const int                                udpPort = 4243;
        static const std::string	                    localAdress = "127.0.0.1";
	}
}
