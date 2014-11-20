#pragma once

#include <cstdint>
#include <vector>
#include <SFML/Graphics.hpp>

class SpriteModel
{
	// ctor - dtor
	public:
		SpriteModel();
		~SpriteModel();

	// coplien form
	private:
		SpriteModel(SpriteModel const &) {}
		SpriteModel const	&operator=(SpriteModel const &) { return *this; }

	// methods
	public:
		uint32_t	getCurrentIndex() const;
		bool		isLoop() const;

		void		setAnims(uint32_t begin, uint32_t end);
		void		setAnims(std::vector<sf::Sprite>::iterator begin, std::vector<sf::Sprite>::iterator end);
		void		setLoop(bool enable = true);

		sf::Sprite const	&getSprite();

	// attributes
	private:
		std::vector<sf::Sprite>	mSprites;
		bool					mLoop;
		uint32_t				mIndex;
		uint32_t				mBegin;
		uint32_t				mEnd;
};
