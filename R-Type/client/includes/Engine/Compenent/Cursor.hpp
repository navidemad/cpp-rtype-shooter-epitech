#pragma once

#include <list>
#include "../Entity.hpp"
#include "../Component.hpp"
#include "../ComponentType.h"
#include "NoCopyable.hpp"

class Cursor : public NoCopyable, public Component
{
	// ctor - dtor
	public:
		Cursor();
		~Cursor();

	public:
		bool			next();
		bool			prev();
		void			addEntity(unsigned int);
		unsigned int	getIdEntity() const;
		void			block();
		bool			isBlocked() const;

	private:
		std::list<unsigned int>				mListEntity;
		std::list<unsigned int>::iterator	mCurrent;
		bool								mBlocked;
};
