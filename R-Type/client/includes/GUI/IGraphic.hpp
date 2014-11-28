#pragma once

#include <string>
#include <cstdint>

class IGraphic
{
	public:
		virtual ~IGraphic()	{}

	// public methods
	public:
		virtual bool	drawSprite(std::string const &key, float delta, float x, float y) = 0;
		virtual bool	drawFont(std::string const &key, std::string const &strn, float x, float y, uint32_t size = 12) = 0;
		virtual bool	playSound(std::string const &key, bool onLoop = false) = 0;
		virtual void	setVolume(std::string const &key, float volume = 100.0) = 0;
		virtual bool	isOpen() const = 0;
		virtual void	handleEvent() = 0;
		virtual void	init() = 0;
		virtual void	update() = 0;
		virtual void	clear() = 0;
		virtual void	show() = 0;
		virtual bool	isPressed(std::string) = 0;
		virtual float	getDelta() = 0;
		virtual void	close() = 0;
};
