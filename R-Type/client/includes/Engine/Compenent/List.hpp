#pragma once

#include <list>
#include <vector>
#include <stdint.h>
#include "Engine/Entity.hpp"
#include "Engine/Component.hpp"


struct information_room
{
	information_room(std::string const &name, int nbPlayerInRoom, int maxPlayer) : mName(name), mNbPlayerInRoom(nbPlayerInRoom), mMaxPlayer(maxPlayer) { }
	std::string	mName;
	int			mNbPlayerInRoom;
	int			mMaxPlayer;

	bool operator==(information_room const & room) const {
		return this->mMaxPlayer == room.mMaxPlayer && this->mName == room.mName && this->mNbPlayerInRoom == room.mNbPlayerInRoom;
	}
	bool operator!=(information_room const & room) const {
		return !(this->mMaxPlayer == room.mMaxPlayer && this->mName == room.mName && this->mNbPlayerInRoom == room.mNbPlayerInRoom);
	}

};

struct List : public Component
{
	public:
		List(unsigned int const);
		~List();

	public:
		void	addRoom(const information_room &);


	public:
		bool	hasTimeElapsed() const;
		void	resetTimer();
		void	updateTimer(uint32_t delta);
		
//	private:
		std::list<information_room>										mListRoom;
		std::vector<std::list<information_room>::iterator>				mListRoomButton;
		std::vector<std::list<information_room>::iterator>::iterator	mCurrentRoom;

//	private:
		const unsigned int												mNbRoomButton;
		uint32_t														mTimeElapsed;
		uint32_t														mCycle;

};