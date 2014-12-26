#pragma once

#include <map>
#include <memory>
#include <string>
#include <SFML/Audio.hpp>
#include "GUI/IResourceManager.hpp"
#include "NoCopyable.hpp"

class MusicManager : public NoCopyable, public IResourceManager<std::string>
{
	// ctor - dtor
	private:
		MusicManager();
	public:
		~MusicManager();

	// instance
	public:
		static const std::shared_ptr<MusicManager>	&getInstance();
	private:
		static std::shared_ptr<MusicManager>	mInstance;

	// methods
	public:
		void					loadResources(std::string const &key, std::string const &path);
		void					unloadResources();
		std::string				&getResource(std::string const &key);

	// attributes
	private:
		std::map<std::string, std::string>		mListResources;
};
