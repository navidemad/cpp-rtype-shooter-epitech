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
		MENU = 0,
		OPTION,
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
		unsigned int				mCurrentId;
		std::vector<ECSManager>		mEngine;
		std::shared_ptr<IGraphic>	mGui;

	private:
		void						init();
		void						initMenu();
		void						initOption();
};
