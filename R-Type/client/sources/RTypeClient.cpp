#include "RTypeClient.hpp"
#include "Engine/Entity.hpp"
#include "GUI/SFMLGraphic.hpp"
#include "Engine/Component.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Drawable.hpp"
#include "Core/DrawableSystem.hpp"
#include "Core/DrawableFontSystem.hpp"
#include "Engine/Compenent/Font.hpp"

RTypeClient::RTypeClient()
	: mCurrentId(RTypeClient::MENU), mEngine(this), mGui(SFMLGraphic::getInstance())
{
}

RTypeClient::~RTypeClient()
{

}

RTypeClient::RTypeClient(RTypeClient const &) : mEngine(this) {}

RTypeClient const	&RTypeClient::operator=(RTypeClient const &) { return *this; }

void	RTypeClient::run()
{
	mGui->init();
	init();

	while (mGui->isOpen())
	{
		mGui->update(); // update graphic engine
		mGui->clear(); // clear graphic engine
		mEngine.updateSystem(); // update gameplay engine
		mGui->show(); // display graphic engine
	}
}

void	RTypeClient::setIdGame(unsigned int currentId)
{
	mCurrentId = currentId;
}

unsigned int	RTypeClient::getIdGame() const
{
	return mCurrentId;
}

void			RTypeClient::init()
{
	initMenu();
}

void			RTypeClient::initMenu()
{
	Entity		&menuScreen = mEngine.createEntity();

	menuScreen.addComponent(new Position(0, 0));
	menuScreen.addComponent(new Drawable("menu"));

	Entity		&logoScreen = mEngine.createEntity();

	logoScreen.addComponent(new Position(900, 60));
	logoScreen.addComponent(new Drawable("logo"));

	Entity		&logoCharacter = mEngine.createEntity();

	logoCharacter.addComponent(new Position(0, 100));
	logoCharacter.addComponent(new Drawable("logoCharacter"));

	Entity		&createGame = mEngine.createEntity();

	createGame.addComponent(new Position(1150, 500));
	createGame.addComponent(new Font("0", "Create room"));

	Entity		&searchGame = mEngine.createEntity();

	searchGame.addComponent(new Position(1150, 585));
	searchGame.addComponent(new Font("0", "Search room"));

	Entity		&optionGame = mEngine.createEntity();

	optionGame.addComponent(new Position(1150, 675));
	optionGame.addComponent(new Font("0", "Option"));

	Entity		&quitGame = mEngine.createEntity();

	quitGame.addComponent(new Position(1150, 770));
	quitGame.addComponent(new Font("0", "Quit"));

	mEngine.addSystem(new DrawableSystem);
	mEngine.addSystem(new DrawableFontSystem);

}