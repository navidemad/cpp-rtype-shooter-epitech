#pragma once

#include "System.hpp"
#include "Engine/Entity.hpp"

class TextInputSystem : public System
{
    // ctor - dtor
    public:
		TextInputSystem();
		~TextInputSystem();

    // copy operators
    public:
		TextInputSystem(const TextInputSystem &) = delete;
		TextInputSystem(TextInputSystem &&) = delete;
		const TextInputSystem &operator=(const TextInputSystem &) = delete;
		const TextInputSystem &operator=(TextInputSystem &&) = delete;

	public:
		void	process(Entity &, uint32_t);

	private:
		uint32_t	mTimeElapsed;
};
