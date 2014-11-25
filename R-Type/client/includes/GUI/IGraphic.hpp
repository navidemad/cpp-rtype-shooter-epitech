#pragma once

#include <cstdint>

class IGraphic
{
	public:
		virtual ~IGraphic()	{}

	// public methods
	public:
		virtual bool	drawSprite(uint32_t id, float delta, uint32_t x, uint32_t y) = 0;
		virtual bool	drawFont(uint32_t id, uint32_t posX, uint32_t posY) = 0;
		virtual bool	playSound(bool onLoop = false) = 0;
		virtual bool	isOpen() const = 0;
		virtual void	handleEvent() = 0;
		virtual void	init() = 0;
};
