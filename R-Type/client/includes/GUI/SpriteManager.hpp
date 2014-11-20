#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"
#include "GUI/SpriteModel.hpp"

class SpriteManager : public IResourceManager<std::vector<SpriteModel>>
{
	// ctor - dtor
	public:
		SpriteManager();
		~SpriteManager();

	// coplien form
	private:
		SpriteManager(SpriteManager const &);
		SpriteManager const	&operator=(SpriteManager const &);

	// methods
	public:
		void							loadResources();
		void							unloadResources();
		std::vector<SpriteModel> const	&getResources() const;

	// attributes
	private:
		std::vector<SpriteModel>	mListResources;
};
