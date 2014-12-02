#pragma once

#include <memory>
#include "Engine/ECSManager.hpp"
#include "GUI/IGraphic.hpp"

class ECSManager;

class RTypeClient
{
public:
	enum Game : unsigned int
	{
		PRESS_START = 0,
		MENU,
		OPTION,
		SEARCH_MENU,
		RTYPE,
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

	public:
		void run();

	// setter getter
	public: 
		void						setIdGame(unsigned int);
		unsigned int				getIdGame() const;
		std::shared_ptr<IGraphic>	getGui() const { return mGui; }

	// Attribute
	private:
		unsigned int							mCurrentId;
		std::vector<ECSManager>					mEngine;
		std::shared_ptr<IGraphic>				mGui;

		std::vector<void (RTypeClient::*)()>	mInit;
		std::vector<void (RTypeClient::*)()>	mStart;
		std::vector<void (RTypeClient::*)()>	mStop;



	private: // init function
		void						init();
		void						initMenu();
		void						initOption();
		void						initPressStart();
		void						initRtype();
		void						initSearchMenu();

	private:
		void						startMenu();
		void						startOption();
		void						startPressStart();
		void						startRtype();
		void						startSearchMenu();

	private:
		void						stopMenu();
		void						stopOption();
		void						stopPressStart();
		void						stopRtype();
		void						stopSearchMenu();

	private:
		void						simulateReceiveClient(unsigned int);
};
