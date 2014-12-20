#pragma once

#include <cstdint>
#include "Engine/Entity.hpp"
#include "Core/System.hpp"
#include "NoCopyable.hpp"

class BackgroundSystem : public System
{
    // ctor - dtor
    public:
		BackgroundSystem();
		~BackgroundSystem();

    public:
	    void	process(Entity &, uint32_t);

};
