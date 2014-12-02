#pragma once

#include <memory>
#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include "GUI/IRessourceManager.hpp"

namespace sf
{
	struct sSound
	{
		std::string		test;
		sf::SoundBuffer	soundBuffer;
		sf::Sound		sound;
	};
}

class SoundManager : public IRessourceManager<sf::sSound>
{
	// ctor - dtor
	private:
		explicit SoundManager();
	public:
		virtual ~SoundManager();

    // copy operators
	public:
        SoundManager(const SoundManager &) = delete;
        SoundManager(SoundManager &&) = delete;
        const SoundManager &operator=(const SoundManager &) = delete;
        const SoundManager &operator=(SoundManager &&) = delete;

	// instance
	public:
		static std::shared_ptr<SoundManager>	getInstance();
	private:
		static std::shared_ptr<SoundManager>	mInstance;

	// methods
	public:
		void					loadResources();
		void					unloadResources();
		sf::sSound				&getResource(std::string const &key);

	// attributes
	private:
		std::map<std::string, sf::sSound>		mListResources;
};
