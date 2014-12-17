#pragma once
#include <QtCore>
#include <memory>
#include "Engine/ECSManager.hpp"
#include "GUI/IGraphic.hpp"
#include "Network/ServerCommunication.hpp"

class ECSManager;

class RTypeClient : public QThread
{
public:
	enum Game : unsigned int
	{
		PRESS_START = 0,
		MENU,
		OPTION,
		SEARCH_MENU,
		CREATE_MENU,
		RTYPE,
		ARTWORK,
		LIMIT
	};
	
	// ctor - dtor
	public:
		RTypeClient();
		~RTypeClient();

	// coplien form
	private:
//		RTypeClient(RTypeClient const &);
		RTypeClient const	&operator=(RTypeClient const &);

	private:
		void run();

	// setter getter
	public: 
		void						setIdGame(unsigned int);
		unsigned int				getIdGame() const;
		std::shared_ptr<IGraphic>	getGui() const { return mGui; }

	// Attribute
	private:
		unsigned int							mCurrentId;
		std::vector<ECSManager *>				mEngine;
		std::shared_ptr<IGraphic>				mGui;
		std::string								mCurrentLevel;
		std::string								mCurrentGame;
		std::string								mScript;
		ServerCommunication						mServer;

		std::vector<void (RTypeClient::*)()>	mInit;
		std::vector<void (RTypeClient::*)()>	mStart;
		std::vector<void (RTypeClient::*)()>	mStop;

		int										mPort;
		std::string								mAdresse;
		std::string								mPseudo;

	private: // init function
		void						init();

		void						initMenu();
		void						initOption();
		void						initPressStart();
		void						initRtype();
		void						initSearchMenu();
		void						initCreateMenu();
		void						initArtwork();

	private:
		void						startMenu();
		void						startOption();
		void						startPressStart();
		void						startRtype();
		void						startSearchMenu();
		void						startCreateMenu();
		void						startArtwork();

	private:
		void						stopMenu();
		void						stopOption();
		void						stopPressStart();
		void						stopRtype();
		void						stopSearchMenu();
		void						stopCreateMenu();
		void						stopArtwork();

	private:
		void						simulateReceiveClient(unsigned int);

	public:
		void	setPort(std::string const &);
		void	setIpAdresse(std::string const &);
		void	setPseudo(std::string const &);
		void	setGame(std::string const &);
		void	setLevel(std::string const &);
		void	setScript(std::string const &);
		bool	createGame();
		void	connectToServer();
};
