#pragma once

#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "GUI/IResourceManager.hpp"
#include "GUI/SpriteModel.hpp"

class SpriteManager : public IResourceManager<SpriteModel>
{
    // ctor - dtor
    private:
        explicit SpriteManager();
    public:
        virtual ~SpriteManager();

    // copy operators
    public:
        SpriteManager(const SpriteManager &) = delete;
        SpriteManager(SpriteManager &&) = delete;
		const SpriteManager &operator=(const SpriteManager &) = delete;
		const SpriteManager &operator=(SpriteManager &&) = delete;

	// instance
	public:
		static std::shared_ptr<SpriteManager>	getInstance();
	private:
		static std::shared_ptr<SpriteManager>	mInstance;

	// nested class for offset sprite if picture contains several sub frame sprites
	public:
		class SpriteOffset
		{
			// ctor - dtor
			public:
				SpriteOffset(uint32_t rectLeft, uint32_t rectTop, uint32_t rectWidth, uint32_t rectHeight);
				~SpriteOffset();

			// coplien form
			private:
				SpriteOffset(SpriteOffset const &) = delete;
				SpriteOffset(SpriteOffset const &&) = delete;
				SpriteOffset const	&operator=(SpriteOffset const &) = delete;
				SpriteOffset const	&operator=(SpriteOffset const &&) = delete;

			// attributes
			private:
				uint32_t	mRectLeft;
				uint32_t	mRectTop;
				uint32_t	mRectWidth;
				uint32_t	mRectHeight;

			// methods
			public:
				uint32_t	getRectLeft() const;
				uint32_t	getRectTop() const;
				uint32_t	getRectWidth() const;
				uint32_t	getRectHeight() const;
		};

	// methods
	public:
		void		loadResources(std::string const &key, std::string const &path);
		void		loadResources(std::string const &key, std::string const &path, uint32_t columns, uint32_t lines, bool loop = false);
		void		loadResources(std::string const &key, std::string const &path, uint32_t columns, uint32_t lines, SpriteOffset const &so, bool loop = false);
		void		unloadResources();
		SpriteModel	&getResource(std::string const &key);

	// attributes
	private:
		std::map<std::string, SpriteModel>	mListResources;
};
