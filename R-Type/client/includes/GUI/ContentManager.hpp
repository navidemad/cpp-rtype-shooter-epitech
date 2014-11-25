#pragma once

#include <memory>
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
