#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IGraphic.hpp"
#include "GUI/ContentManager.hpp"

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
		bool	drawSprite(uint32_t id, uint32_t posX, uint32_t posY);
		bool	drawFont(uint32_t id, uint32_t posX, uint32_t posY);
		bool	playSound(bool onLoop = false);
		bool	isOpen() const;
		void	handleEvent();
		void	show();
		void	clear();

		sf::Window const						&getWindow() const;
		std::map<sf::Event, std::string> const	&getKeyEvents() const;

	// private method
	private:
		void	init();

	// attributes
	private:
		sf::RenderWindow					mWindow;
		std::map<sf::Event, std::string>	mKeyEvents;
		ContentManager						mContentManager;
};
