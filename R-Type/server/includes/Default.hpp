#pragma once

#include <string>
#include <cstdint>
#include <map>
#include "IResource.hpp"

namespace Config
{
	namespace Window
	{
        static const float Width = 1920.f;
        static const float Height = 1080.f;
	}

	namespace Game
	{
        static const float	                            fpsLimit = 30.f;
        static const uint64_t	                        minIdComponent = 6;
        static const int                                maxPlayersInAGame = 4;
        static const int                                maxSpectatorsInAGame = 4;
        static std::map<IResource::Direction, float>    angleTab = {
            { IResource::Direction::RIGHT, 0.f },
            { IResource::Direction::BOTTOM, 90.f },
            { IResource::Direction::LEFT, 180.f },
            { IResource::Direction::TOP, 270.f }
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
