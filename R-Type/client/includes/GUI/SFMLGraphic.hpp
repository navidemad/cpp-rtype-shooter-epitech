#pragma once

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IGraphic.hpp"
#include "GUI/ContentManager.hpp"
#include "Core/InputManager.hpp"

class SFMLGraphic : public IGraphic
{
    // ctor - dtor
    private:
        SFMLGraphic();
	public:
        virtual ~SFMLGraphic();

    // copy operators
    public:
        SFMLGraphic(const SFMLGraphic &) = delete;
        SFMLGraphic(SFMLGraphic &&) = delete;
        const SFMLGraphic &operator=(const SFMLGraphic &) = delete;
        const SFMLGraphic &operator=(SFMLGraphic &&) = delete;

	// instance
	public:
		static std::shared_ptr<IGraphic>	getInstance();
	private:
		static std::shared_ptr<IGraphic>	mInstance;

	// public methods
	public:
		bool	drawSprite(std::string const &key, float delta, float x, float y);
		void	update();
		bool	drawFont(std::string const &key, std::string const &str, float x, float y);
		bool	playSound(std::string const &key, bool onLoop = false);
		void	setVolume(std::string const &key, float volume);
		bool	isOpen() const;
		void	handleEvent();
		void	show();
		void	clear();
		bool	isPressed(std::string);
		sf::RenderWindow						&getWindow();

	// public method
	public:
		void	init();

	// attributes
	private:
		sf::RenderWindow					mWindow;
		std::map<sf::Event, std::string>	mKeyEvents;
		ContentManager						mContentManager;
		InputManager						mInputManager;
};
