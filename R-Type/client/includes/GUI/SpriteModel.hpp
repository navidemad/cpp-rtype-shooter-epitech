#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <SFML/Graphics.hpp>

class SpriteModel
{
    // ctor - dtor
    public:
        explicit SpriteModel(std::string const &filename, uint32_t lines, uint32_t columns);
        ~SpriteModel();

    // copy operators
    public:
        SpriteModel(const SpriteModel &) = delete;
        SpriteModel(SpriteModel &&) = delete;
        const SpriteModel &operator=(const SpriteModel &) = delete;
        const SpriteModel &operator=(SpriteModel &&) = delete;

	// methods
	public:
		uint32_t			getCurrentIndex() const;
		bool				isLoop() const;
		std::string const	&getFileName() const;
		sf::Sprite const	&getSprite() const;
		sf::IntRect const	&getFrame(uint32_t index) const;

		void				setAnims(uint32_t begin, uint32_t end);
		void				setCurrentIndex(uint32_t currentIndex);
		void				setLoop(bool enable = true);
	private:
		void				init();

	// attributes
	private:
		sf::Texture					mTexture;
		sf::Sprite					mSprite;
		std::vector<sf::IntRect>	mFrames;
		bool						mLoop;
		std::string					mFileName;
		uint32_t					mCurrentIndex;
		uint32_t					mBegin;
		uint32_t					mEnd;
		uint32_t					mLines;
		uint32_t					mColumns;
		uint32_t					mPosX;
		uint32_t					mPosY;
};
