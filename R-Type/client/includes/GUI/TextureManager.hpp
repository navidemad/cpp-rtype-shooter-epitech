#pragma once

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"

class TextureManager : public IResourceManager<std::map<std::string, sf::Sprite>>
{
	// ctor, coplien form
	private:
		TextureManager();
		TextureManager(TextureManager const &) = delete;
		TextureManager(TextureManager const &&) = delete;
		TextureManager const	&operator=(TextureManager const &) = delete;
		TextureManager const	&operator=(TextureManager const &&) = delete;

	// dtor
	public:
		~TextureManager();

	// instance
	public:
		static std::shared_ptr<TextureManager>	getInstance(void);
	private:
		static std::shared_ptr<TextureManager>	mInstance;

	// methods
	public:
		void									loadResources();
		void									unloadResources();
		std::map<std::string, sf::Sprite> const	&getResources() const;

	// attributes
	private:
		std::map<std::string, sf::Sprite>	mListResources;
};
