#pragma once

#include <list>
#include "../Entity.hpp"
#include "../Component.hpp"
#include "../ComponentType.h"

class Cursor : public Component
{
	// ctor - dtor
	public:
		Cursor();
		~Cursor();

	// coplien form
	private:
		Cursor(Cursor const &) : Component(ComponentType::CURSOR) {}
		Cursor const	&operator=(Cursor const &) { return *this; }
		
	public:
		bool			next();
		bool			prev();
		void			addEntity(unsigned int);
		unsigned int	getIdEntity();
		void			block();
		bool			isBlocked() const;

	private:
		std::list<unsigned int>				mListEntity;
		std::list<unsigned int>::iterator	mCurrent;
		bool								mBlocked;
};
