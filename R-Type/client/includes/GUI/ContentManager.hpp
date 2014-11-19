#pragma once

#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"

class ContentManager
{
	// ctor - dtor
	public:
		ContentManager();
		~ContentManager();

	// coplien form
	private:
		ContentManager(ContentManager const &) {}
		ContentManager const	&operator=(ContentManager const &) { return *this; }

	// methods
	public:
		void	loadTextures();
		void	loadFonts();
		void	loadSounds();

		std::map<std::string, sf::Sprite> const	&getTextures() const;
		std::map<std::string, sf::Font> const	&getFonts() const;
		std::map<std::string, sf::Sound> const	&getSounds() const;

	// attributes
	private:
		IResourceManager<std::map<std::string, sf::Sprite>>	*mTextures;
		IResourceManager<std::map<std::string, sf::Font>>	*mFonts;
		IResourceManager<std::map<std::string, sf::Sound>>	*mSounds;
};
