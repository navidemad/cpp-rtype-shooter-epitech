#pragma once

#include "IResource.hpp"
#include "IDynLib.hpp"
#include "Timer.hpp"
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
            void setX(double x);
            void setY(double y);
            void setWidth(double width);
            void setHeight(double height);
            void setAngle(short angle);
            void setMoveSpeed(double speed);
            void setFireDeltaTime(double speed);
            void setLife(double life);
            void setId(uint64_t id);
            void setType(IResource::Type type);
            void setOwnerId(uint64_t ownerId);
            void setResource(IResource*);

        // getters
        public:
            double getX(void) const;
            double getY(void) const;
            double getWidth(void) const;
            double getHeight(void) const;
            short getAngle(void) const;
            double getMoveSpeed(void) const;
            double getFireDeltaTime(void) const;
            double getLife(void) const;
            uint64_t getId(void) const;
            IResource::Type getType(void) const;
            uint64_t getOwnerId(void) const;
            IResource* getResource(void) const;
            const std::shared_ptr<IDynLib> &getDynLib(void) const;

        // attributes
        private:
            Timer mFireTimer;
        private:
			double mX;
			double mY;
			double mWidth;
			double mHeight;
            short mAngle;
            double mMoveSpeed;
            double mFireDeltaTime;
			double mLife;
            uint64_t mId;
            uint64_t mOwnerId;
            IResource::Type mType;
            IResource* mResource;
            std::shared_ptr<IDynLib> mDynLib;
        };

}
