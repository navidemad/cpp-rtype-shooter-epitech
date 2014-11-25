#pragma once

#include <memory>
#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"
#include "GUI/SpriteModel.hpp"
#include "GUI/TextureManager.hpp"
#include "GUI/SpriteManager.hpp"
#include "GUI/FontManager.hpp"
#include "Audio/SoundManager.hpp"

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

		std::map<std::string, sf::Sprite> const			&getTextures() const;
		std::vector<std::shared_ptr<SpriteModel>> const	&getSprites() const;
		std::map<std::string, sf::Font> const			&getFonts() const;
		std::map<std::string, sf::Sound> const			&getSounds() const;

	// attributes
	private:
		std::shared_ptr<IResourceManager<std::map<std::string, sf::Sprite>>>	mTextures;
		std::shared_ptr<IResourceManager<std::vector<std::shared_ptr<SpriteModel>>>>	mSprites;
		std::shared_ptr<IResourceManager<std::map<std::string, sf::Font>>>		mFonts;
		std::shared_ptr<IResourceManager<std::map<std::string, sf::Sound>>>		mSounds;
};
