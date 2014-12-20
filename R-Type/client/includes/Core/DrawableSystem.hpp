#pragma once

#include "Core/System.hpp"
#include "Engine/Entity.hpp"
#include "NoCopyable.hpp"

class DrawableSystem : public System
{
    // ctor - dtor
    public:
		DrawableSystem();
		~DrawableSystem() { }

    public:
        void	process(Entity &, uint32_t);
	    void	process();

};
