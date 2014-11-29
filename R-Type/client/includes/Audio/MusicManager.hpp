#pragma once

#include <map>
#include <memory>
#include <string>
#include <SFML/Audio.hpp>
#include "GUI/IResourceManager.hpp"

class MusicManager : public IResourceManager<std::string>
{
	// ctor - dtor
	private:
		explicit MusicManager();
	public:
		~MusicManager();

	// copy operator
	public:
		MusicManager(const MusicManager &) = delete;
		MusicManager(MusicManager &&) = delete;
		const MusicManager &operator=(const MusicManager &) = delete;
		const MusicManager &operator=(MusicManager &&) = delete;

	// instance
	public:
		static std::shared_ptr<MusicManager>	getInstance();
	private:
		static std::shared_ptr<MusicManager>	mInstance;

	// methods
	public:
		void					loadResources();
		void					unloadResources();
		std::string				&getResource(std::string const &key);

	// attributes
	private:
		std::map<std::string, std::string>		mListResources;
};
