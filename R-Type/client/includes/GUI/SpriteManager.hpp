#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"
#include "GUI/SpriteModel.hpp"

class SpriteManager : public IResourceManager<std::vector<std::shared_ptr<SpriteModel>>>
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
		void											loadResources();
		void											unloadResources();
		std::vector<std::shared_ptr<SpriteModel>> const	&getResources() const;

	// attributes
	private:
		std::vector<std::shared_ptr<SpriteModel>>		mListResources;
};
