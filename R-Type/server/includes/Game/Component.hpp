#pragma once

#include "IResource.hpp"
#include <cstdint>

namespace NGame
{

    class Component {

        // ctor / dtor
        public:
            explicit Component(uint64_t id = 0);
            Component(const Component& rhs);
            Component& operator=(const Component& rhs);
            ~Component(void) = default;

        // setters
        public:
            void setX(double x);
            void setY(double y);
            void setWidth(double width);
            void setHeight(double height);
            void setAngle(short angle);
            void setSpeed(double speed);
            void setLife(double life);
            void setId(uint64_t id);
            void setType(IResource::Type type);

        // getters
        public:
            double getX(void) const;
            double getY(void) const;
            double getWidth(void) const;
            double getHeight(void) const;
            short getAngle(void) const;
            double getSpeed(void) const;
            double getLife(void) const;
            uint64_t getId(void) const;
            IResource::Type getType(void) const;

        // attributes
        private:
			double mX;
			double mY;
			double mWidth;
			double mHeight;
			short mAngle;
			double mSpeed;
			double mLife;
            uint64_t mId;
            IResource::Type mType;

        };

}
