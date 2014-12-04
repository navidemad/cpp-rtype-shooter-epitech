#pragma once

#include <string>
#include <cstdint>

class IGraphic
{
	public:
		virtual ~IGraphic()	{}

	// public methods
	public:
		virtual bool				drawSprite(std::string const &key, uint32_t delta, float x, float y, uint32_t id) = 0;
		virtual bool				drawFont(std::string const &key, std::string const &strn, float x, float y, uint32_t size = 12) = 0;
		virtual bool				playSound(std::string const &key, bool onLoop = false) = 0;
		virtual bool				playMusic(std::string const &key, bool onLoop = true) = 0;
		virtual void				stopMusic() = 0;
		virtual void				stopSound(std::string const &key) = 0;
		virtual void				setVolume(std::string const &key, float volume = 100.0) = 0;
		virtual std::string	const	&getInputText() const = 0;

//		virtual void				loadSprite(std::string const &key, std::string const &path) = 0;
//		virtual void				loadSound(std::string const &key, std::string const &path) = 0;

		virtual bool				isOpen() const = 0;
		virtual void				handleEvent() = 0;
		virtual void				init() = 0;
		virtual void				update() = 0;
		virtual void				clear() = 0;
		virtual void				show() = 0;
		virtual bool				isPressed(std::string) = 0;
		virtual uint32_t			getDelta() = 0;
		virtual void				close() = 0;
};
