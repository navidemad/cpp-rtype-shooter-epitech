#pragma once

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"

class TextureManager : public IResourceManager<sf::Texture>
{
    // ctor - dtor
    private:
        explicit TextureManager();
    public:
        virtual ~TextureManager();

    // copy operators
    public:
        TextureManager(const TextureManager &) = delete;
        TextureManager(TextureManager &&) = delete;
        const TextureManager &operator=(const TextureManager &) = delete;
        const TextureManager &operator=(TextureManager &&) = delete;

	// instance
	public:
		static std::shared_ptr<TextureManager>	getInstance(void);
	private:
		static std::shared_ptr<TextureManager>	mInstance;

	// methods
	public:
		void		loadResources(std::string const &key, std::string const &path);
		void		unloadResources();
		sf::Texture	&getResource(std::string const &key);

	// attributes
	private:
		std::map<std::string, sf::Texture>	mListResources;
};
