#include <memory>
#include "GUI/ContentManager.hpp"

ContentManager::ContentManager() :
	mTextures(TextureManager::getInstance()), 
	mSprites(SpriteManager::getInstance()), 
	mFonts(FontManager::getInstance()), 
	mMusics(MusicManager::getInstance()),
	mSounds(SoundManager::getInstance())
{
}

ContentManager::~ContentManager()
{
}

void	ContentManager::loadTextures()
{
	mTextures->loadResources("", "");
}

void	ContentManager::loadSprites()
{
	std::static_pointer_cast<SpriteManager>(mSprites)->loadResources("menu", "assets/sprites/menu.png");
	std::static_pointer_cast<SpriteManager>(mSprites)->loadResources("logo", "assets/sprites/logo.png");
	std::static_pointer_cast<SpriteManager>(mSprites)->loadResources("logoCharacter", "assets/sprites/logoCharacter.png");
	std::static_pointer_cast<SpriteManager>(mSprites)->loadResources("logoSearch", "assets/sprites/logoSearch.png");
	std::static_pointer_cast<SpriteManager>(mSprites)->loadResources("logoOption", "assets/sprites/logoOption.png");
	std::static_pointer_cast<SpriteManager>(mSprites)->loadResources("searchBar", "assets/sprites/search_bar.png");
	std::static_pointer_cast<SpriteManager>(mSprites)->loadResources("ball", "assets/sprites/r-typesheet3.gif", 12, 1, true);
	std::static_pointer_cast<SpriteManager>(mSprites)->loadResources("cursor", "assets/sprites/cursor.png");
}

void	ContentManager::loadFonts()
{
	mFonts->loadResources("0", "./assets/fonts/RemachineScript_Personal_Use.ttf");
}

void	ContentManager::loadMusics()
{
	mMusics->loadResources("Menu", "./assets/musics/Touhou_8/[01] Eternal Night Vignette ~ Eastern Night.ogg");
	mMusics->loadResources("Game", "./assets/musics/Touhou_8/[02] Illusionary Night ~ Ghostly Eyes.ogg");
	mMusics->loadResources("Boss", "./assets/musics/Touhou_8/[08] Retribution for the Eternal Night ~ Imperishable Night.ogg");
}

void	ContentManager::loadSounds()
{
	mSounds->loadResources("change_option", "./assets/sounds/efx/se_ok00.wav");
	mSounds->loadResources("option", "./assets/sounds/efx/se_option.wav");
	mSounds->loadResources("pause", "./assets/sounds/efx/se_pause.wav");
	mSounds->loadResources("pldead", "./assets/sounds/efx/se_pldead00.wav");
}

std::shared_ptr<IResourceManager<sf::Texture>> const	&ContentManager::getTextures() const
{
	return mTextures;
}

std::shared_ptr<IResourceManager<SpriteModel>>			&ContentManager::getSprites()
{
	return mSprites;
}

std::shared_ptr<IResourceManager<sf::Font>> const		&ContentManager::getFonts() const
{
	return mFonts;
}

std::shared_ptr<IResourceManager<std::string>> const		&ContentManager::getMusics() const
{
	return mMusics;
}

std::shared_ptr<IResourceManager<sf::sSound>> const		&ContentManager::getSounds() const
{
	return mSounds;
}
