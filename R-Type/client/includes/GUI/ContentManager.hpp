#pragma once

#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"
#include "GUI/SpriteModel.hpp"

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
		void	loadSprites();
		void	loadFonts();
		void	loadSounds();

		std::map<std::string, sf::Sprite> const		&getTextures() const;
		std::vector<SpriteModel> const	&getSprites() const;
		std::map<std::string, sf::Font> const		&getFonts() const;
		std::map<std::string, sf::Sound> const		&getSounds() const;

	// attributes
	private:
		IResourceManager<std::map<std::string, sf::Sprite>>	*mTextures;
		IResourceManager<std::vector<SpriteModel>>			*mSprites;
		IResourceManager<std::map<std::string, sf::Font>>	*mFonts;
		IResourceManager<std::map<std::string, sf::Sound>>	*mSounds;
};
