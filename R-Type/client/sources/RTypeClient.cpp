#include <algorithm>
#include <sstream>
#include "Default.hpp"
#include "RTypeClient.hpp"
#include "Gameplay/Gameplay.hpp"
#include "Gameplay/GameplaySystem.hpp"
#include "Engine/Entity.hpp"
#include "Engine/ECSManagerNetwork.hpp"
#include "GUI/SFMLGraphic.hpp"
#include "Engine/Component.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Velocity.hpp"
#include "Engine/Compenent/Background.hpp"
#include "Engine/Compenent/Cursor.hpp"
#include "Engine/Compenent/Drawable.hpp"
#include "Engine/Compenent/Button.hpp"
#include "Engine/Compenent/List.hpp"
#include "Core/ScriptSystem.hpp"
#include "Core/DrawableSystem.hpp"
#include "Core/BackgroundSystem.hpp"
#include "Core/VelocitySystem.hpp"
#include "Core/TextInputSystem.hpp"
#include "Core/DrawableFontSystem.hpp"
#include "Core/ButtonSystem.hpp"
#include "Core/ListSystem.hpp"
#include "Engine/Compenent/Font.hpp"
#include "Engine/Compenent/TextInput.hpp"

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(IResource::Direction)

RTypeClient::RTypeClient()
: mCurrentId(RTypeClient::PRESS_START), mEngine(RTypeClient::LIMIT), mGui(SFMLGraphic::getInstance()), mCurrentLevel(Config::Game::defaultLevelGame), mCurrentGame(Config::Game::defaultNameGame), mServer(Config::Network::port), mInit(RTypeClient::LIMIT), mStart(RTypeClient::LIMIT), mStop(RTypeClient::LIMIT)
{
	mEngine[PRESS_START] = new ECSManager;
	mEngine[MENU] = new ECSManager;
	mEngine[OPTION] = new ECSManager;
	mEngine[CREATE_MENU] = new ECSManager;
	mEngine[SEARCH_MENU] = new ECSManagerNetwork;
	mEngine[RTYPE] = new ECSManagerNetwork;

	mInit[PRESS_START] = &RTypeClient::initPressStart;
	mInit[MENU] = &RTypeClient::initMenu;
	mInit[OPTION] = &RTypeClient::initOption;
	mInit[CREATE_MENU] = &RTypeClient::initCreateMenu;
	mInit[SEARCH_MENU] = &RTypeClient::initSearchMenu;
	mInit[RTYPE] = &RTypeClient::initRtype;

	mStart[PRESS_START] = &RTypeClient::startPressStart;
	mStart[MENU] = &RTypeClient::startMenu;
	mStart[OPTION] = &RTypeClient::startOption;
	mStart[CREATE_MENU] = &RTypeClient::startCreateMenu;
	mStart[SEARCH_MENU] = &RTypeClient::startSearchMenu;
	mStart[RTYPE] = &RTypeClient::startRtype;

	mStop[PRESS_START] = &RTypeClient::stopPressStart;
	mStop[MENU] = &RTypeClient::stopMenu;
	mStop[OPTION] = &RTypeClient::stopOption;
	mStop[CREATE_MENU] = &RTypeClient::stopCreateMenu;
	mStop[SEARCH_MENU] = &RTypeClient::stopSearchMenu;
	mStop[RTYPE] = &RTypeClient::stopRtype;

	for (ECSManager *engine : mEngine)
	{
		engine->setClient(this);
	}

	//connect ecs and serverCom
	ECSManagerNetwork *searchMenu	= static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU]);
	ECSManagerNetwork *rtype		= static_cast<ECSManagerNetwork *>(mEngine[RTYPE]);

	searchMenu->OnDestroyResource(5);
	QObject::connect(searchMenu, SIGNAL(SignalCreateGame(const std::string &, const std::string &, int, int)), &mServer, SLOT(OnCreateGame(const std::string &, const std::string &, int, int)));
	QObject::connect(searchMenu, SIGNAL(SignalDeleteGame(const std::string &)), &mServer, SLOT(OnDeleteGame(const std::string &)));
	QObject::connect(rtype, SIGNAL(SignalFire()), &mServer, SLOT(OnFire()));
	QObject::connect(searchMenu, SIGNAL(SignalJoinGame(const std::string &)), &mServer, SLOT(OnJoinGame(const std::string &)));
	QObject::connect(searchMenu, SIGNAL(SignalLeaveGame()), &mServer, SLOT(OnLeaveGame()));
	QObject::connect(searchMenu, SIGNAL(SignalListGame()), &mServer, SLOT(OnListGame()));
	QObject::connect(searchMenu, SIGNAL(SignalListLevel()), &mServer, SLOT(OnListLevel()));
	QObject::connect(rtype, SIGNAL(SignalMove(IResource::Direction)), &mServer, SLOT(OnMove(IResource::Direction)));
	QObject::connect(searchMenu, SIGNAL(SignalObserveGame(const std::string &)), &mServer, SLOT(OnObserveGame(const std::string &)));
	QObject::connect(searchMenu, SIGNAL(SignalShowGame(const std::string &)), &mServer, SLOT(OnShowGame(const std::string &)));
	QObject::connect(searchMenu, SIGNAL(SignalUpdatePseudo(const std::string &)), &mServer, SLOT(OnUpdatePseudo(const std::string &)));
	QObject::connect(searchMenu, SIGNAL(SignalSetServerIp(const std::string &)), &mServer, SLOT(OnSetServerIp(const std::string &)));
	QObject::connect(searchMenu, SIGNAL(SignalSetServerPortTcp(int)), &mServer, SLOT(OnSetServerPortTcp(int)));
	QObject::connect(searchMenu, SIGNAL(SignalConnectToServer()), &mServer, SLOT(OnConnectToServer()));

	QObject::connect(&mServer, SIGNAL(SignalDestroyResource(int)), rtype, SLOT(OnDestroyResource(int)));
	QObject::connect(&mServer, SIGNAL(SignalEndGame(const std::string &)), rtype, SLOT(OnEndGame(const std::string &)));
	QObject::connect(&mServer, SIGNAL(SignalError(ICommand::Instruction, ErrorStatus::Error)), searchMenu, SLOT(OnError(ICommand::Instruction, ErrorStatus::Error)));
	QObject::connect(&mServer, SIGNAL(SignalMoveResource(IResource::Type, float, float, short, int)), rtype, SLOT(OnMoveResource(IResource::Type, float, float, short, int)));
	QObject::connect(&mServer, SIGNAL(SignalShowGame(const std::string &, const std::string &, int, int, int, int)), searchMenu, SLOT(OnShowGame(const std::string &, const std::string &, int, int, int, int)));
	QObject::connect(&mServer, SIGNAL(SignalShowLevel(const std::string &, const std::string &)), searchMenu, SLOT(OnShowLevel(const std::string &, const std::string &)));
	QObject::connect(&mServer, SIGNAL(SignalTimeElapse(int64_t)), rtype, SLOT(OnTimeElapse(int64_t)));
	QObject::connect(&mServer, SIGNAL(SignalUpdateScore(const std::string & , int, int)), rtype, SLOT(OnUpdateScore(const std::string & , int, int)));
	QObject::connect(&mServer, SIGNAL(SignalCloseSocket()), searchMenu, SLOT(OnCloseSocket()));
	QObject::connect(&mServer, SIGNAL(SignalFailConnect()), searchMenu, SLOT(OnFailConnect()));
}

RTypeClient::~RTypeClient()
{
	for (auto engine : mEngine)
	{
		delete engine;
	}
}

//RTypeClient::RTypeClient(RTypeClient const &) : mEngine(this) {}

RTypeClient const	&RTypeClient::operator=(RTypeClient const &) { return *this; }

void	RTypeClient::run()
{

	mGui->init();
	init();

	while (mGui->isOpen())
	{
		uint64_t delta = mGui->getDelta();
		unsigned int	id = mCurrentId;

		mGui->clear(); // clear graphic engine
		mGui->update(); // update graphic engine
		mEngine[mCurrentId]->updateSystem(delta); // update gameplay engine
		mGui->show(); // display graphic engine

		if (id != mCurrentId)
		{
			(this->*(mStop[id]))();
			(this->*(mStart[mCurrentId]))();
		}
	}
}

void	RTypeClient::setIdGame(unsigned int currentId)
{
	mCurrentId = currentId;
	mEngine[currentId]->start();
}

unsigned int	RTypeClient::getIdGame() const
{
	return mCurrentId;
}

void			RTypeClient::init()
{
	auto init = [this](void (RTypeClient::*ptr)(void)) {
		(this->*ptr)();
	};
	(this->*(this->mStart[this->mCurrentId]))();
	std::for_each(mInit.begin(), mInit.end(), init);

	static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalSetServerIp(Config::Network::adress);
	static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalSetServerPortTcp(Config::Network::port);
	static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalConnectToServer();
}

void			RTypeClient::initRtype()
{
	ECSManager &engine = *mEngine[RTypeClient::RTYPE];

	Entity		&fire = engine.createEntity();
	fire.addComponent(new Fire);

	Entity		&left = engine.createEntity();
	left.addComponent(new Left);

	Entity		&up = engine.createEntity();
	up.addComponent(new Up);

	Entity		&right = engine.createEntity();
	right.addComponent(new Right);

	Entity		&down = engine.createEntity();
	down.addComponent(new Down);

	Entity		&background = engine.createEntity();

	Background *backgroundPtr = new Background;
	background.addComponent(backgroundPtr);

	for (unsigned int i = 0; i != (Config::Window::x / Config::Title::sizeTitleBackground) + 2; ++i)
	{
		Entity &backgroundSprite = engine.createEntity();

		Position *pos = new Position(Config::Title::sizeTitleBackground * i, 0);

		backgroundPtr->addBackground(pos);

		backgroundSprite.addComponent(new Drawable("background"));
		backgroundSprite.addComponent(pos);
		backgroundSprite.addComponent(new Velocity(-1, 0, 8000));
	}
	//gameplay system
	engine.addSystem(new UpSystem);
	engine.addSystem(new DownSystem);
	engine.addSystem(new LeftSystem);
	engine.addSystem(new RightSystem);
	engine.addSystem(new FireSystem);
	engine.addSystem(new ScriptSystem);

	// content system
	engine.addSystem(new DrawableSystem);
	engine.addSystem(new ButtonSystem);
	engine.addSystem(new DrawableFontSystem);
	engine.addSystem(new VelocitySystem);

	//background system
	engine.addSystem(new BackgroundSystem);

	engine.setFirstId(engine.getCurrentId());
}

void			RTypeClient::initSearchMenu()
{
	ECSManager &engine = *mEngine[RTypeClient::SEARCH_MENU];

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

	Entity		&runGame = engine.createEntity();
	cursor->addEntity(runGame.getId());

	runGame.addComponent(new Position(1150, 400));
	runGame.addComponent(new Font("0", "Run game !"));
	runGame.addComponent(new ButtonMenuGame());

	Entity		&quitGame = engine.createEntity();
	cursor->addEntity(quitGame.getId());

	quitGame.addComponent(new Position(1600, 950));
	quitGame.addComponent(new Font("0", "Quit"));
	quitGame.addComponent(new ButtonMenuGame());

	Entity		&searchMenu = engine.createEntity();

	searchMenu.addComponent(new Position(1000, 500));
	searchMenu.addComponent(new List(&RTypeClient::setGame));
	searchMenu.addComponent(new Font("0", ""));

	Entity		&logoCharacter = engine.createEntity();

	logoCharacter.addComponent(new Position(0, 100));
	logoCharacter.addComponent(new Drawable("logoSearch"));

	engine.addSystem(new DrawableSystem);
	engine.addSystem(new ButtonSystem);
	engine.addSystem(new DrawableFontSystem);
	engine.addSystem(new ListSystem);

}

void			RTypeClient::initOption()
{
	ECSManager &engine = *mEngine[RTypeClient::OPTION];
	
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
	Font	*fontPortGame = new Font("0", std::to_string(Config::Network::port));

	inputPortGame.addComponent(new Position(1400, 400));
	inputPortGame.addComponent(fontPortGame);

	Entity		portGame = engine.createEntity();
	cursor->addEntity(portGame.getId());

	portGame.addComponent(new Position(1020, 400));
	portGame.addComponent(new Font("0", "Port server "));
	portGame.addComponent(new ButtonInput(fontPortGame, &RTypeClient::setPort));

	Entity		inputAdressGame = engine.createEntity();
	Font	*fontAdressGame = new Font("0", Config::Network::adress);

	inputAdressGame.addComponent(new Position(1400, 500));
	inputAdressGame.addComponent(fontAdressGame);

	Entity		adressGame = engine.createEntity();
	cursor->addEntity(adressGame.getId());

	Entity		&logoCharacter = engine.createEntity();

	logoCharacter.addComponent(new Position(0, 400));
	logoCharacter.addComponent(new Drawable("logoOption"));

	adressGame.addComponent(new Position(960, 500));
	adressGame.addComponent(new Font("0", "Adress server "));
	adressGame.addComponent(new ButtonInput(fontAdressGame, &RTypeClient::setIpAdresse));

	Entity		pseudoGame = engine.createEntity();
	Font	*fontPseudoGame = new Font("0", Config::Network::defaultPseudo);

	pseudoGame.addComponent(new Position(1400, 600));
	pseudoGame.addComponent(fontPseudoGame);

	Entity		pseudoGameButton = engine.createEntity();
	cursor->addEntity(pseudoGameButton.getId());

	pseudoGameButton.addComponent(new Position(1170, 600));
	pseudoGameButton.addComponent(new Font("0", "Pseudo"));
	pseudoGameButton.addComponent(new ButtonInput(fontPseudoGame, &RTypeClient::setPseudo));


	Entity		backGame = engine.createEntity();
	cursor->addEntity(backGame.getId());

	backGame.addComponent(new Position(1150, 900));
	backGame.addComponent(new Font("0", "Go back without saving !"));
	backGame.addComponent(new ButtonMenuGame());

	engine.addSystem(new DrawableSystem);
	engine.addSystem(new ButtonSystem);
	engine.addSystem(new DrawableFontSystem);
}

void			RTypeClient::initCreateMenu()
{
	ECSManager &engine = *mEngine[RTypeClient::CREATE_MENU];

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
	Font	*fontPortGame = new Font("0", Config::Game::defaultNameGame);

	inputPortGame.addComponent(new Position(800, 400));
	inputPortGame.addComponent(fontPortGame);

	Entity		portGame = engine.createEntity();
	cursor->addEntity(portGame.getId());

	portGame.addComponent(new Position(420, 400));
	portGame.addComponent(new Font("0", "Nom du game "));
	portGame.addComponent(new ButtonInput(fontPortGame, &RTypeClient::setGame));

	Entity		&logoCharacter = engine.createEntity();

	logoCharacter.addComponent(new Position(0, 400));
	logoCharacter.addComponent(new Drawable("logoOption"));

	Entity		&createGame = engine.createEntity();
	cursor->addEntity(createGame.getId());

	createGame.addComponent(new Position(420, 500));
	createGame.addComponent(new Font("0", "Creer la partie "));
	createGame.addComponent(new ButtonCreateGame());

	Entity		backGame = engine.createEntity();
	cursor->addEntity(backGame.getId());

	backGame.addComponent(new Position(1150, 900));
	backGame.addComponent(new Font("0", "Go back !"));
	backGame.addComponent(new ButtonMenuGame());

	engine.addSystem(new DrawableSystem);
	engine.addSystem(new ButtonSystem);
	engine.addSystem(new DrawableFontSystem);

}

void			RTypeClient::initPressStart()
{
	ECSManager &engine = *mEngine[RTypeClient::PRESS_START];

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
	ECSManager &engine = *mEngine[RTypeClient::MENU];

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
	searchGame.addComponent(new ButtonSearchMenu());

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

void	RTypeClient::startMenu()
{
	mGui->playMusic("Menu");
}
void	RTypeClient::startOption()
{
	mGui->playMusic("Menu");
}

void	RTypeClient::startPressStart()
{
	mGui->playMusic("Menu");
}

void	RTypeClient::startRtype()
{
	mGui->playMusic("Game");
	static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalJoinGame(mCurrentGame);
}

void	RTypeClient::startSearchMenu()
{
	//static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalListGame();
}

void			RTypeClient::startCreateMenu()
{
	mGui->playMusic("Menu");
	static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalListLevel();
}

void	RTypeClient::stopMenu()
{

}
void	RTypeClient::stopOption()
{

}

void	RTypeClient::stopPressStart()
{
}

void	RTypeClient::stopRtype()
{

}
void	RTypeClient::stopSearchMenu()
{
	Entity &entity = mEngine[SEARCH_MENU]->getEntityWithSpecificCompenent(ComponentType::LIST);

	List *component = static_cast<List *>(entity.getSpecificComponent(ComponentType::LIST));
	component->clear();
}

void			RTypeClient::stopCreateMenu()
{

}

void	RTypeClient::setPort(std::string const &port)
{
	std::istringstream buffer(port);
	int value;
	buffer >> value;

	static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalSetServerPortTcp(value);
	static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalConnectToServer();
}

void	RTypeClient::setIpAdresse(std::string const &addr)
{
	static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalSetServerIp(addr);
	static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalConnectToServer();
}

void	RTypeClient::setPseudo(std::string const &pseudo)
{
	static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalUpdatePseudo(pseudo);
}

void	RTypeClient::setGame(std::string const &game)
{
	std::cout << game << std::endl;
	mCurrentGame = game;
}

void	RTypeClient::setLevel(std::string const &level)
{
	std::cout << level << std::endl;
	mCurrentLevel = level;
}

void	RTypeClient::setScript(std::string const &script)
{
	mScript = script;
}

bool	RTypeClient::createGame()
{
	std::cout << mCurrentGame << " " << mCurrentLevel << std::endl;
	static_cast<ECSManagerNetwork *>(mEngine[SEARCH_MENU])->SignalCreateGame(mCurrentGame, mCurrentLevel,  4, 4);
	return true;
}
