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
            void setX(short x);
            void setY(short y);
            void setWidth(short width);
            void setHeight(short height);
            void setAngle(short angle);
            void setMoveSpeed(double speed);
            void setFireDeltaTime(double speed);
            void setLife(short life);
            void setId(uint64_t id);
            void setType(IResource::Type type);
            void setOwner(const std::shared_ptr<User> &owner);
            void setResource(IResource*);

        // getters
        public:
            short getX(void) const;
            short getY(void) const;
            short getWidth(void) const;
            short getHeight(void) const;
            short getAngle(void) const;
            double getMoveSpeed(void) const;
            double getFireDeltaTime(void) const;
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
            short mX;
            short mY;
            short mWidth;
            short mHeight;
            short mAngle;
            double mMoveSpeed;
            double mFireDeltaTime;
            short mLife;
            uint64_t mId;
            std::shared_ptr<User> mOwner;
            IResource::Type mType;
            IResource* mResource;
            std::shared_ptr<IDynLib> mDynLib;
        };

}
