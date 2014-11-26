#include "RTypeClient.hpp"
#include "Engine/Entity.hpp"
#include "GUI/SFMLGraphic.hpp"
#include "Engine/Component.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Cursor.hpp"
#include "Engine/Compenent/Drawable.hpp"
#include "Engine/Compenent/Button.hpp"
#include "Core/DrawableSystem.hpp"
#include "Core/DrawableFontSystem.hpp"
#include "Core/ButtonSystem.hpp"
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

#include <iostream>

void			RTypeClient::initMenu()
{

	mGui->playSound("mgs", false);

	Entity		&menuScreen = mEngine.createEntity();
	
	menuScreen.addComponent(new Position(0, 0));
	menuScreen.addComponent(new Drawable("menu"));

	Entity		&logoScreen = mEngine.createEntity();

	logoScreen.addComponent(new Position(900, 60));
	logoScreen.addComponent(new Drawable("logo"));

	Entity		&cursorGame = mEngine.createEntity();
	Cursor		*cursor = new Cursor();

	cursorGame.addComponent(new Position(0, 500));
	cursorGame.addComponent(cursor);
	cursorGame.addComponent(new Drawable("searchBar"));

	Entity		&createGame = mEngine.createEntity();
	cursor->addEntity(createGame.getId());

	createGame.addComponent(new Position(1150, 500));
	createGame.addComponent(new Font("0", "Create room"));
	createGame.addComponent(new ButtonGame());
	
	Entity		&searchGame = mEngine.createEntity();
	cursor->addEntity(searchGame.getId());

	searchGame.addComponent(new Position(1150, 585));
	searchGame.addComponent(new Font("0", "Search room"));

	Entity		&optionGame = mEngine.createEntity();
	cursor->addEntity(optionGame.getId());

	optionGame.addComponent(new Position(1150, 675));
	optionGame.addComponent(new Font("0", "Option"));

	Entity		&quitGame = mEngine.createEntity();
	cursor->addEntity(quitGame.getId());

	quitGame.addComponent(new Position(1150, 770));
	quitGame.addComponent(new Font("0", "Quit"));

	Entity		&logoCharacter = mEngine.createEntity();

	logoCharacter.addComponent(new Position(0, 100));
	logoCharacter.addComponent(new Drawable("logoCharacter"));


	mEngine.addSystem(new DrawableSystem);
	mEngine.addSystem(new ButtonSystem);
	mEngine.addSystem(new DrawableFontSystem);
}