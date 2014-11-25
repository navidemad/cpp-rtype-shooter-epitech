#pragma once

#include <memory>
#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include "GUI/IResourceManager.hpp"

class SoundManager : public IResourceManager<std::map<std::string, sf::Sound>>
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
		virtual void									loadResources();
		virtual void									unloadResources();
		virtual std::map<std::string, sf::Sound> const	&getResources() const;

	// attributes
	private:
		std::map<std::string, sf::Sound>		mListResources;
};
