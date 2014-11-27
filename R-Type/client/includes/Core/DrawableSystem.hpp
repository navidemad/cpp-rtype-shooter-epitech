#pragma once

#include "Core/System.hpp"
#include "Engine/Entity.hpp"

class DrawableSystem : public System
{
    // ctor - dtor
    public:
		explicit DrawableSystem();
		~DrawableSystem() { }

		void	process(Entity &, float);
public:
	void	process();
    // copy operators
/*    public:
        DrawableSystem(const DrawableSystem &) = delete;
        DrawableSystem(DrawableSystem &&) = delete;
        const DrawableSystem &operator=(const DrawableSystem &) = delete;
        const DrawableSystem &operator=(DrawableSystem &&) = delete;*/
};
