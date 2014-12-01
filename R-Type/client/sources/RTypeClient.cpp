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
#include "Core/TextInputSystem.hpp"
#include "Core/DrawableFontSystem.hpp"
#include "Core/ButtonSystem.hpp"
#include "Engine/Compenent/Font.hpp"
#include "Engine/Compenent/TextInput.hpp"

RTypeClient::RTypeClient()
: mCurrentId(RTypeClient::PRESS_START), mEngine(RTypeClient::LIMIT), mGui(SFMLGraphic::getInstance())
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
		uint32_t delta = mGui->getDelta();

		mGui->clear(); // clear graphic engine
		mGui->update(); // update graphic engine
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
	initPressStart();
	startMenu();
}

void		RTypeClient::startMenu()
{
	mGui->playMusic("Menu");
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

	Entity		&cursorGame = engine.createEntity();
	Cursor		*cursor = new Cursor();

	cursorGame.addComponent(new Position(0, 500));
	cursorGame.addComponent(cursor);
	cursorGame.addComponent(new Drawable("searchBar"));

	Entity		inputPortGame = engine.createEntity();

	inputPortGame.addComponent(new Position(1400, 400));
	inputPortGame.addComponent(new TextInput("0", "4242"));

	Entity		portGame = engine.createEntity();
	cursor->addEntity(portGame.getId());

	portGame.addComponent(new Position(1020, 400));
	portGame.addComponent(new Font("0", "Port server "));
	portGame.addComponent(new ButtonInput(inputPortGame.getId()));

	Entity		inputAdressGame = engine.createEntity();

	inputAdressGame.addComponent(new Position(1400, 500));
	inputAdressGame.addComponent(new TextInput("0", "127.0.0.1"));

	Entity		adressGame = engine.createEntity();
	cursor->addEntity(adressGame.getId());

	adressGame.addComponent(new Position(960, 500));
	adressGame.addComponent(new Font("0", "Adress server "));
	adressGame.addComponent(new ButtonInput(inputAdressGame.getId()));


	Entity		backGame = engine.createEntity();
	cursor->addEntity(backGame.getId());

	backGame.addComponent(new Position(1150, 900));
	backGame.addComponent(new Font("0", "Go back without saving !"));
	backGame.addComponent(new ButtonMenuGame());

	engine.addSystem(new DrawableSystem);
	engine.addSystem(new ButtonSystem);
	engine.addSystem(new TextInputSystem);
	engine.addSystem(new DrawableFontSystem);
}

void			RTypeClient::initPressStart()
{
	ECSManager &engine = mEngine[RTypeClient::PRESS_START];

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

	Entity		&createGame = engine.createEntity();
	cursor->addEntity(createGame.getId());

	createGame.addComponent(new Position(800, 500));
	createGame.addComponent(new Font("0", "Press enter"));
	createGame.addComponent(new ButtonMenuGame());

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
	optionGame.addComponent(new ButtonOption());

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