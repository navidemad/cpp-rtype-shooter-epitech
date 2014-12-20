#pragma once

#include "System.hpp"
#include "Engine/Entity.hpp"
#include "NoCopyable.hpp"

class TextInputSystem : public System
{
    // ctor - dtor
    public:
		TextInputSystem();
		~TextInputSystem();

	public:
		void	process(Entity &, uint32_t);

	private:
		uint32_t	mTimeElapsed;
};
