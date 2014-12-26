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
	//mTextures->loadResources("", "");
}

void	ContentManager::loadSprites()
{
	auto sprites = std::static_pointer_cast<SpriteManager>(mSprites);

	// sprites use essentially for GUI's menu
	sprites->loadResources("menu", "assets/sprites/menu.png");
	sprites->loadResources("logo", "assets/sprites/logo.png");
	sprites->loadResources("background", "assets/sprites/background1.png");
	sprites->loadResources("logoCharacter", "assets/sprites/logoCharacter.png");
	sprites->loadResources("logoSearch", "assets/sprites/logoSearch.png");
	sprites->loadResources("logoOption", "assets/sprites/logoOption.png");
	sprites->loadResources("searchBar", "assets/sprites/search_bar.png");
	sprites->loadResources("cursor", "assets/sprites/cursor.png");

	// sprites use essentially for ingame
	sprites->loadResources("bullet", "assets/sprites/r-typesheet1.gif", 4, 1, SpriteManager::SpriteOffset(130, 18, 136, 32), true); // tir gauche à droite
	sprites->loadResources("bulletReverse", "assets/sprites/r-typesheet1.gif", 4, 1, SpriteManager::SpriteOffset(266, 18, 136, 32), true); // tir droite à gauche
	sprites->loadResources("player", "assets/sprites/r-typesheet42.gif", 5, 1, SpriteManager::SpriteOffset(0, 0, 166, 21), true);
    sprites->loadResources("caster", "assets/sprites/r-typesheet14.gif", 5, 1, SpriteManager::SpriteOffset(0, 0, 250, 50), true);
    sprites->loadResources("melee", "assets/sprites/r-typesheet14.gif", 5, 1, SpriteManager::SpriteOffset(0, 0, 250, 50), true); // a changer
    sprites->loadResources("super", "assets/sprites/r-typesheet14.gif", 5, 1, SpriteManager::SpriteOffset(0, 0, 250, 50), true); // a changer
    sprites->loadResources("satellite", "assets/sprites/r-typesheet2.gif", 12, 1, SpriteManager::SpriteOffset(157, 34, 288, 24), true);

	// load sketches drawing by tran_y on smartphone 5.2" (Xperia Z2 with pen/pencil)
	sprites->loadResources("sketch01", "assets/sprites/sketchs/sketch-1418753217209.jpg");
	sprites->loadResources("sketch02", "assets/sprites/sketchs/sketch-1418753311635.jpg");
	sprites->loadResources("sketch03", "assets/sprites/sketchs/sketch-1418753348961.jpg");
	sprites->loadResources("sketch04", "assets/sprites/sketchs/sketch-1418753417319.jpg");
}

void	ContentManager::loadFonts()
{
	mFonts->loadResources("0", "./assets/fonts/RemachineScript_Personal_Use.ttf");
}

void	ContentManager::loadMusics()
{
	//mMusics->loadResources("Menu", "./assets/musics/Touhou_8/[01] Eternal Night Vignette ~ Eastern Night.ogg");
	//mMusics->loadResources("Game", "./assets/musics/Touhou_8/[02] Illusionary Night ~ Ghostly Eyes.ogg");
	//mMusics->loadResources("Boss", "./assets/musics/Touhou_8/[08] Retribution for the Eternal Night ~ Imperishable Night.ogg");

	mMusics->loadResources("Menu", "./assets/musics/FFXIII/01_-_Prelude_to_FINAL_FANTASY_XIII.ogg");
	mMusics->loadResources("Game", "./assets/musics/FFXIII/01_-_Blinded_By_Light.ogg");
	mMusics->loadResources("Boss", "./assets/musics/FFXIII/05_-_Saber_39_s_Edge.ogg");
}

void	ContentManager::loadSounds()
{
	mSounds->loadResources("change_option", "./assets/sounds/efx/se_ok00.wav");
	mSounds->loadResources("option", "./assets/sounds/efx/se_option.wav");
	mSounds->loadResources("pause", "./assets/sounds/efx/se_pause.wav");
	mSounds->loadResources("pldead", "./assets/sounds/efx/se_pldead00.wav");
	mSounds->loadResources("shot", "./assets/sounds/efx/se_tan00.wav");
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
