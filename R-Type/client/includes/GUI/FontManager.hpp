#pragma once

#include <memory>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"
#include "NoCopyable.hpp"

class FontManager : public NoCopyable, public IResourceManager<sf::Font>
{
	// ctor - dtor
	private:
		FontManager();
	public:
		~FontManager();

	// instance
	public:
		static std::shared_ptr<FontManager>		getInstance();
	private:
		static std::shared_ptr<FontManager>		mInstance;

	// methods
	public:
		void		loadResources(std::string const &key, std::string const &path);
		void		unloadResources();
		sf::Font	&getResource(std::string const &key);

	// attributes
	private:
		std::map<std::string, sf::Font>	mListResources;
};
