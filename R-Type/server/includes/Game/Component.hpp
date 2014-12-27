#pragma once

#include "IResource.hpp"
#include "IDynLib.hpp"
#include "Timer.hpp"
#include "User.hpp"
#include "NoCopyable.hpp"

#include <queue>
#include <chrono>
#include <memory>
#include <cstdint>

namespace NGame
{

    class Component : public NoCopyable {

        // ctor / dtor
        public:
            explicit Component(uint64_t id = 0);
            ~Component(void) = default;

        // rate frame
        public:
            bool canFire(void);

        // struct rectangle
        public:
            bool intersect(const std::shared_ptr<Component>& rhs) const;

        // setters
        public:
            void setX(float x);
            void setY(float y);
            void setWidth(float width);
            void setHeight(float height);
            void setAngle(float angle);
            void setMoveSpeed(float speed);
            void setFireDeltaTime(float speed);
            void setLife(short life);
            void setId(uint64_t id);
            void setType(IResource::Type type);
            void setOwner(const std::shared_ptr<User> &owner);
            void setResource(IResource*);

        // getters
        public:
            float getX(void) const;
            float getY(void) const;
            float getWidth(void) const;
            float getHeight(void) const;
            float getAngle(void) const;
            float getMoveSpeed(void) const;
            float getFireDeltaTime(void) const;
            short getLife(void) const;
            uint64_t getId(void) const;
            IResource::Type getType(void) const;
            std::shared_ptr<User> &getOwner(void);
            IResource* getResource(void) const;
            const std::shared_ptr<IDynLib> &getDynLib(void) const;

        // attributes
        private:
            Timer mFireTimer;
        private:
            float mX;
            float mY;
            float mWidth;
            float mHeight;
            float mAngle;
            float mMoveSpeed;
            float mFireDeltaTime;
            short mLife;
            uint64_t mId;
            std::shared_ptr<User> mOwner;
            IResource::Type mType;
            IResource* mResource;
            std::shared_ptr<IDynLib> mDynLib;
        };

}
