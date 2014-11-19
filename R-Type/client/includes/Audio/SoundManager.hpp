#pragma once

#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include "GUI/IResourceManager.hpp"

class SoundManager : public IResourceManager<std::map<std::string, sf::Sound>>
{
	// ctor - dtor
	public:
		SoundManager();
		~SoundManager();

	// coplien form
	private:
		SoundManager(SoundManager const &) {}
		SoundManager const	&operator=(SoundManager const &) { return *this; }

	// methods
	public:
		void									loadResources();
		void									unloadResources();
		std::map<std::string, sf::Sound> const	&getResources() const;

	// attributes
	private:
		std::map<std::string, sf::Sound>	mListResources;
};
