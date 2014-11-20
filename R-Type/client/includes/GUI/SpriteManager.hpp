#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"
#include "GUI/SpriteModel.hpp"

class SpriteManager : public IResourceManager<std::vector<SpriteModel>>
{
	// ctor - dtor
	private:
		SpriteManager();
		~SpriteManager();

	private:
		SpriteManager(SpriteManager const &) = delete;
		SpriteManager(SpriteManager const &&) = delete;
		SpriteManager const	&operator=(SpriteManager const &) = delete;
		SpriteManager const	&operator=(SpriteManager const &&) = delete;

	// instance
	public:
		static std::shared_ptr<SpriteManager>	getInstance();
	private:
		static std::shared_ptr<SpriteManager>	mInstance;

	// methods
	public:
		void							loadResources();
		void							unloadResources();
		std::vector<SpriteModel> const	&getResources() const;

	// attributes
	private:
		std::vector<SpriteModel>	mListResources;
};
