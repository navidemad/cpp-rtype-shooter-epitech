#pragma once

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"
#include "NoCopyable.hpp"

class TextureManager : public NoCopyable, public IResourceManager<sf::Texture>
{
    // ctor - dtor
    private:
        TextureManager();
    public:
        virtual ~TextureManager();

	// instance
	public:
		static const std::shared_ptr<TextureManager>	&getInstance(void);
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
