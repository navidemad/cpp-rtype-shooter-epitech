#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"

class TextureManager : public IResourceManager<std::map<std::string, sf::Sprite>>
{
	// ctor - dtor
	public:
		TextureManager();
		~TextureManager();

	// coplien form
	private:
		TextureManager(TextureManager const &) {}
		TextureManager const	&operator=(TextureManager const &) { return *this; }

	// methods
	public:
		void									loadResources();
		void									unloadResources();
		std::map<std::string, sf::Sprite> const	&getResources() const;

	// attributes
	private:
		std::map<std::string, sf::Sprite>	mListResources;
};
