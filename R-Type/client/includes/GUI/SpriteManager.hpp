#pragma once

#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"
#include "GUI/SpriteModel.hpp"

class SpriteManager : public IResourceManager<SpriteModel>
{
    // ctor - dtor
    private:
        explicit SpriteManager();
    public:
        virtual ~SpriteManager();

    // copy operators
    public:
        SpriteManager(const SpriteManager &) = delete;
        SpriteManager(SpriteManager &&) = delete;
		const SpriteManager &operator=(const SpriteManager &) = delete;
		const SpriteManager &operator=(SpriteManager &&) = delete;

	// instance
	public:
		static std::shared_ptr<SpriteManager>	getInstance();
	private:
		static std::shared_ptr<SpriteManager>	mInstance;

	// methods
	public:
		void		loadResources(std::string const &key, std::string const &path);
		void		unloadResources();
		SpriteModel	&getResource(std::string const &key);

	// attributes
	private:
		std::map<std::string, SpriteModel>	mListResources;
};
