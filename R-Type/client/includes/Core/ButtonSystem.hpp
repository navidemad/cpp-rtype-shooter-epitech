#pragma once

#include "System.hpp"
#include "Engine/Entity.hpp"

class ButtonSystem : public System
{
    // ctor - dtor
    public:
        explicit ButtonSystem();
        ~ButtonSystem();

	public:
		void	process(Entity &, float);
    // copy operators
    public:
        ButtonSystem(const ButtonSystem &) = delete;
        ButtonSystem(ButtonSystem &&) = delete;
        const ButtonSystem &operator=(const ButtonSystem &) = delete;
        const ButtonSystem &operator=(ButtonSystem &&) = delete;

	private:
		float	mTimeElapsed;
};
