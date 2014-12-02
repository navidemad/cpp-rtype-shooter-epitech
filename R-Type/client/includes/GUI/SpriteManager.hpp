#pragma once

#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IRessourceManager.hpp"
#include "GUI/SpriteModel.hpp"

class SpriteManager : public IRessourceManager<SpriteModel>
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
		void		loadResources();
		void		unloadResources();
		SpriteModel	&getResource(std::string const &key);

	// attributes
	private:
		std::map<std::string, SpriteModel>	mListResources;
};
