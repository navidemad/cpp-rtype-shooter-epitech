#pragma once

#include "System.hpp"
#include "Engine/Entity.hpp"
#include "NoCopyable.hpp"

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

	private:
		uint32_t	mTimeElapsed;
};
