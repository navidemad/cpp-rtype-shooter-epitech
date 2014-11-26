#pragma once

#include <memory>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"

class FontManager : public IResourceManager<sf::Font>
{
	// ctor - dtor
	private:
		FontManager();
	public:
		~FontManager();

    // copy operators
	public:
		FontManager(FontManager const &) = delete;
		FontManager(FontManager const &&) = delete;
		FontManager const	&operator=(FontManager const &) = delete;
		FontManager const	&operator=(FontManager const &&) = delete;

	// instance
	public:
		static std::shared_ptr<FontManager>		getInstance();
	private:
		static std::shared_ptr<FontManager>		mInstance;

	// methods
	public:
		void		loadResources();
		void		unloadResources();
		sf::Font	&getResource(std::string const &key);

	// attributes
	private:
		std::map<std::string, sf::Font>	mListResources;
};
