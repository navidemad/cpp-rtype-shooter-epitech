#pragma once

#include "Peer.hpp"
#include "IResource.hpp"

namespace NGame
{

    class Component {

        // ctor / dtor
        public:
            explicit Component(int userId = -1) : mUserId(userId) { }
            ~Component(void) { }

        // setters
        public:
            void setX(double x) { mX = x; }
            void setY(double y) { mY = y; }
            void setWidth(int width) { mWidth = width; }
            void setHeight(int height) { mHeight = height; }
            void setAngle(double angle) { mAngle = angle; }
            void setSpeed(double speed) { mSpeed = speed; }
            void setLife(int life) { mLife = life; }
            void setType(IResource::Type type) { mType = type; }
            void setId(uint64_t id) { mUserId = id; }

        // getters
        public:
			double getX(void) const { return mX; }
			double getY(void) const { return mY; }
            int getWidth(void) const { return mWidth; }
            int getHeight(void) const { return mHeight; }
            double getAngle(void) const { return mAngle; }
			double getSpeed(void) const { return mSpeed; }
            int getLife(void) const { return mLife; }
            IResource::Type getType(void) { return mType; }
            uint64_t getId(void) const { return mUserId; }

        // attributes
        private:
			double mX;
			double mY;
            int mWidth;
            int mHeight;
			double mAngle;
			double mSpeed;
            int mLife;
            IResource::Type mType;
            uint64_t mUserId;

        };

}
