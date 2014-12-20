#pragma once

#include "Core/System.hpp"
#include "Engine/Entity.hpp"
#include "NoCopyable.hpp"

class DrawableFontSystem : public System
{
    // ctor - dtor
    public:
		DrawableFontSystem();
		~DrawableFontSystem() { }
 	
    public:
        void	process(Entity &, uint32_t);
	    void	process();

};
