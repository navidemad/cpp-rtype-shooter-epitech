#include <algorithm>
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
: mCurrentId(RTypeClient::MENU), mEngine(RTypeClient::LIMIT), mGui(SFMLGraphic::getInstance())
{
	for (ECSManager &engine : mEngine)
	{
		engine.setClient(this);
	}
}

RTypeClient::~RTypeClient()
{

}

//RTypeClient::RTypeClient(RTypeClient const &) : mEngine(this) {}

RTypeClient const	&RTypeClient::operator=(RTypeClient const &) { return *this; }

void	RTypeClient::run()
{
	mGui->init();
	init();

	while (mGui->isOpen())
	{
		float delta = mGui->getDelta();

		mGui->update(); // update graphic engine
		mGui->clear(); // clear graphic engine
		mEngine[mCurrentId].updateSystem(delta); // update gameplay engine
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
	initOption();
}

void			RTypeClient::initOption()
{
	ECSManager &engine = mEngine[RTypeClient::OPTION];

	Entity		&menuScreen = engine.createEntity();

	menuScreen.addComponent(new Position(0, 0));
	menuScreen.addComponent(new Drawable("menu"));

	Entity		&logoScreen = engine.createEntity();

	logoScreen.addComponent(new Position(900, 60));
	logoScreen.addComponent(new Drawable("logo"));

	engine.addSystem(new DrawableSystem);
	engine.addSystem(new ButtonSystem);
	engine.addSystem(new DrawableFontSystem);
}

void			RTypeClient::initMenu()
{
	ECSManager &engine = mEngine[RTypeClient::MENU];

	Entity		&menuScreen = engine.createEntity();
	
	menuScreen.addComponent(new Position(0, 0));
	menuScreen.addComponent(new Drawable("menu"));

	Entity		&logoScreen = engine.createEntity();

	logoScreen.addComponent(new Position(900, 60));
	logoScreen.addComponent(new Drawable("logo"));

	Entity		&cursorGame = engine.createEntity();
	Cursor		*cursor = new Cursor();

	cursorGame.addComponent(new Position(0, 500));
	cursorGame.addComponent(cursor);
	cursorGame.addComponent(new Drawable("searchBar"));

	Entity		&createGame = engine.createEntity();
	cursor->addEntity(createGame.getId());

	createGame.addComponent(new Position(1150, 500));
	createGame.addComponent(new Font("0", "Create room"));
	createGame.addComponent(new ButtonGame());
	
	Entity		&searchGame = engine.createEntity();
	cursor->addEntity(searchGame.getId());

	searchGame.addComponent(new Position(1150, 585));
	searchGame.addComponent(new Font("0", "Search room"));

	Entity		&optionGame = engine.createEntity();
	cursor->addEntity(optionGame.getId());

	optionGame.addComponent(new Position(1150, 675));
	optionGame.addComponent(new Font("0", "Option"));

	Entity		&quitGame = engine.createEntity();
	cursor->addEntity(quitGame.getId());

	quitGame.addComponent(new Position(1150, 770));
	quitGame.addComponent(new Font("0", "Quit"));
	quitGame.addComponent(new ButtonQuitGame());

	Entity		&logoCharacter = engine.createEntity();

	logoCharacter.addComponent(new Position(0, 100));
	logoCharacter.addComponent(new Drawable("logoCharacter"));

	engine.addSystem(new DrawableSystem);
	engine.addSystem(new ButtonSystem);
	engine.addSystem(new DrawableFontSystem);
}