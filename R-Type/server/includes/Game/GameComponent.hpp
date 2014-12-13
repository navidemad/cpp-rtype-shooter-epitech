#pragma once

#include "Peer.hpp"
#include "IResource.hpp"

namespace NGame
{

    class Component {

        // ctor / dtor
        public:
            explicit Component(uint64_t id = 0) : mId(id), mType(IResource::Type::UNKNOWN) { }
			Component(const Component &other) {
				mX = other.getX();
				mY = other.getY();
				mWidth = other.getWidth();
				mHeight = other.getHeight();
				mAngle = other.getAngle();
				mSpeed = other.getSpeed();
				mLife = other.getLife();
				mType = other.getType();
				mId = other.getId();
			}
            ~Component(void) { }

        // setters
        public:
            void setX(double x) { mX = x; }
            void setY(double y) { mY = y; }
            void setWidth(double width) { mWidth = width; }
            void setHeight(double height) { mHeight = height; }
            void setAngle(short angle) { mAngle = angle; }
            void setSpeed(double speed) { mSpeed = speed; }
            void setLife(double life) { mLife = life; }
            void setType(IResource::Type type) { mType = type; }
            void setId(uint64_t id) { mId = id; }

        // getters
        public:
			double getX(void) const { return mX; }
			double getY(void) const { return mY; }
			double getWidth(void) const { return mWidth; }
			double getHeight(void) const { return mHeight; }
			short getAngle(void) const { return mAngle; }
			double getSpeed(void) const { return mSpeed; }
			double getLife(void) const { return mLife; }
            IResource::Type getType(void) const { return mType; }
            uint64_t getId(void) const { return mId; }

        // attributes
        private:
			double mX;
			double mY;
			double mWidth;
			double mHeight;
			short mAngle;
			double mSpeed;
			double mLife;
            IResource::Type mType;
            uint64_t mId;

        };

}
