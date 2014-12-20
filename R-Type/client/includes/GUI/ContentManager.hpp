#pragma once

#include <memory>
#include <string>
#include <map>
#include <cstdint>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"
#include "GUI/SpriteModel.hpp"
#include "GUI/TextureManager.hpp"
#include "GUI/SpriteManager.hpp"
#include "GUI/FontManager.hpp"
#include "Audio/MusicManager.hpp"
#include "Audio/SoundManager.hpp"
#include "NoCopyable.hpp"

class ContentManager : public NoCopyable
{
    // ctor - dtor
    public:
        ContentManager();
        ~ContentManager();

	// methods
	public:
		void	loadTextures();
		void	loadSprites();
		void	loadFonts();
		void	loadMusics();
		void	loadSounds();

		std::shared_ptr<IResourceManager<sf::Texture>> const	&getTextures() const;
		std::shared_ptr<IResourceManager<SpriteModel>> 			&getSprites(); // Sprite must be modifiable
		std::shared_ptr<IResourceManager<sf::Font>> const		&getFonts() const;
		std::shared_ptr<IResourceManager<std::string>> const	&getMusics() const;
		std::shared_ptr<IResourceManager<sf::sSound>> const		&getSounds() const;

	// attributes
	private:
		std::shared_ptr<IResourceManager<sf::Texture>>	mTextures;
		std::shared_ptr<IResourceManager<SpriteModel>>	mSprites;
		std::shared_ptr<IResourceManager<sf::Font>>		mFonts;
		std::shared_ptr<IResourceManager<std::string>>	mMusics;
		std::shared_ptr<IResourceManager<sf::sSound>>	mSounds;
};
