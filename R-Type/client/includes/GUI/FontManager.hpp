#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"

class FontManager : public IResourceManager<std::map<std::string, sf::Font>>
{
	// ctor - dtor
	public:
		FontManager();
		~FontManager();

	// coplien form
	private:
		FontManager(FontManager const &) {}
		FontManager const	&operator=(FontManager const &) { return *this; }

	// methods
	public:
		void									loadResources();
		void									unloadResources();
		std::map<std::string, sf::Font> const	&getResources() const;

	// attributes
	private:
		std::map<std::string, sf::Font>	mListResources;
};
