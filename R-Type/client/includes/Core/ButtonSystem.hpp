#pragma once

#include "System.hpp"
#include "Engine/Entity.hpp"

class ButtonSystem : public System
{
    // ctor - dtor
    public:
        ButtonSystem();
        ~ButtonSystem();

	public:
		void	process(Entity &, uint32_t);

	private:
		bool	hasTimeElapsed() const;

    // copy operators
    public:
        ButtonSystem(const ButtonSystem &) = delete;
        ButtonSystem(ButtonSystem &&) = delete;
        const ButtonSystem &operator=(const ButtonSystem &) = delete;
        const ButtonSystem &operator=(ButtonSystem &&) = delete;

	private:
		uint32_t	mTimeElapsed;
};
