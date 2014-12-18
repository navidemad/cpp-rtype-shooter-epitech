#pragma once

#include <cstdint>
#include "Engine/Entity.hpp"
#include "Core/System.hpp"

class BackgroundSystem : public System
{
    // ctor - dtor
    public:
		BackgroundSystem();
		~BackgroundSystem();

public:
	void	process(Entity &, uint32_t);
    // copy operators
    public:
		BackgroundSystem(const BackgroundSystem &) = delete;
		BackgroundSystem(BackgroundSystem &&) = delete;
		const BackgroundSystem &operator=(const BackgroundSystem &) = delete;
		const BackgroundSystem &operator=(BackgroundSystem &&) = delete;
};
