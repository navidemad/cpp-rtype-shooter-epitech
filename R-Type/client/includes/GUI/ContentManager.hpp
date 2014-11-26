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
        explicit ContentManager();
        ~ContentManager();

    // copy operators
    public:
        ContentManager(const ContentManager &) = delete;
        ContentManager(ContentManager &&) = delete;
        const ContentManager &operator=(const ContentManager &) = delete;
        const ContentManager &operator=(ContentManager &&) = delete;

	// methods
	public:
		void	loadTextures();
		void	loadSprites();
		void	loadFonts();
		void	loadSounds();

		std::shared_ptr<IResourceManager<sf::Texture>> const	&getTextures() const;
		std::shared_ptr<IResourceManager<SpriteModel>> 			&getSprites(); // Sprite must be modifiable
		std::shared_ptr<IResourceManager<sf::Font>> const		&getFonts() const;
		std::shared_ptr<IResourceManager<sf::Sound>> const		&getSounds() const;

	// attributes
	private:
		std::shared_ptr<IResourceManager<sf::Texture>>	mTextures;
		std::shared_ptr<IResourceManager<SpriteModel>>	mSprites;
		std::shared_ptr<IResourceManager<sf::Font>>		mFonts;
		std::shared_ptr<IResourceManager<sf::Sound>>	mSounds;
};
