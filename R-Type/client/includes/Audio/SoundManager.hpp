#pragma once

#include <memory>
#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include "GUI/IResourceManager.hpp"
#include "NoCopyable.hpp"

namespace sf
{
	struct sSound
	{
		sf::SoundBuffer	soundBuffer;
		sf::Sound		sound;
	};
}

class SoundManager : public NoCopyable, public IResourceManager<sf::sSound>
{
	// ctor - dtor
	private:
		SoundManager();
	public:
		virtual ~SoundManager();

	// instance
	public:
		static std::shared_ptr<SoundManager>	getInstance();
	private:
		static std::shared_ptr<SoundManager>	mInstance;

	// methods
	public:
		void					loadResources(std::string const &key, std::string const &path);
		void					unloadResources();
		sf::sSound				&getResource(std::string const &key);

	// attributes
	private:
		std::map<std::string, sf::sSound>		mListResources;
};
