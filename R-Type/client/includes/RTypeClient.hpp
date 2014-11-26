#pragma once


#include "Engine/ECSManager.hpp"
#include "GUI/IGraphic.hpp"

class ECSManager;

class RTypeClient
{
public:
	enum Game : unsigned int
	{
		MENU = 0,
		RTYPE = 1
	};
	
	// ctor - dtor
	public:
		RTypeClient();
		~RTypeClient();

	// coplien form
	private:
		RTypeClient(RTypeClient const &);
		RTypeClient const	&operator=(RTypeClient const &);

	public:
		void run();

	// setter getter
	public: 
		void			setIdGame(unsigned int);
		unsigned int	getIdGame() const;
		IGraphic		*getGui() const { return mGui; }

	// Attribute
	private:
		unsigned int	mCurrentId;
		ECSManager		mEngine;
		IGraphic		*mGui;

	private:
		void			init();
		void			initMenu();
};
