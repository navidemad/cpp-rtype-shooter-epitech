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
		SFMLGraphic();
		~SFMLGraphic();

	// coplien form
	private:
		SFMLGraphic(SFMLGraphic const &) {}
		SFMLGraphic const	&operator=(SFMLGraphic const &) { return *this; }

	// public methods
	public:
		bool	drawSprite();
		bool	drawFont();
		bool	playSound(bool onLoop = false);
		bool	isOpen() const;
		void	handleEvent();

		sf::Window const						&getWindow() const;
		std::map<sf::Event, std::string> const	&getKeyEvents() const;

	// private method
	private:
		void	init();

	// attributes
	private:
		sf::Window							mWindow;
		std::map<sf::Event, std::string>	mKeyEvents;
		ContentManager						mContentManager;
};
