#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IGraphic.hpp"
#include "GUI/ContentManager.hpp"
#include "Core/InputManager.hpp"

class SFMLGraphic : public IGraphic
{
    // ctor - dtor
    public:
        explicit SFMLGraphic();
        ~SFMLGraphic();

    // copy operators
    public:
        SFMLGraphic(const SFMLGraphic &) = delete;
        SFMLGraphic(SFMLGraphic &&) = delete;
        const SFMLGraphic &operator=(const SFMLGraphic &) = delete;
        const SFMLGraphic &operator=(SFMLGraphic &&) = delete;

	// public methods
	public:
		bool	drawSprite(std::string const &key, float delta, float x, float y);
		void	update();
		bool	drawFont(std::string const &key, std::string const &str, float x, float y);
		bool	playSound(bool onLoop = false);
		bool	isOpen() const;
		void	handleEvent();
		void	show();
		void	clear();

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
