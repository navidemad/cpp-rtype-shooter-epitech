#pragma once

#include "Core/System.hpp"
#include "Engine/Entity.hpp"

class DrawableFontSystem : public System
{
    // ctor - dtor
    public:
		explicit DrawableFontSystem();
		~DrawableFontSystem() { }

		void	process(Entity &, uint32_t);
public:
	void	process();
    // copy operators
/*    public:
        DrawableSystem(const DrawableSystem &) = delete;
        DrawableSystem(DrawableSystem &&) = delete;
        const DrawableSystem &operator=(const DrawableSystem &) = delete;
        const DrawableSystem &operator=(DrawableSystem &&) = delete;*/
};
