#pragma once

class IGraphic
{
	public:
		virtual ~IGraphic()	{}

	// public methods
	public:
		virtual bool	drawSprite() = 0;
		virtual bool	drawFont() = 0;
		virtual bool	playSound(bool onLoop = false) = 0;
		virtual bool	isOpen() const = 0;
		virtual void	handleEvent() = 0;

	// private method
	private:
		virtual void	init() = 0;
};
