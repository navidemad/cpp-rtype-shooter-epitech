#include "Component.hpp"

NGame::Component::Component(uint64_t id) : mId(id), mType(IResource::Type::UNKNOWN) { }

NGame::Component::Component(const NGame::Component& rhs) {
    if (this != &rhs) {
        mX = rhs.getX();
        mY = rhs.getY();
        mWidth = rhs.getWidth();
        mHeight = rhs.getHeight();
        mAngle = rhs.getAngle();
        mSpeed = rhs.getSpeed();
        mLife = rhs.getLife();
        mId = rhs.getId();
        mType = rhs.getType();
    }
}
NGame::Component& NGame::Component::operator = (const NGame::Component& rhs) {
    if (this != &rhs) {
        mX = rhs.getX();
        mY = rhs.getY();
        mWidth = rhs.getWidth();
        mHeight = rhs.getHeight();
        mAngle = rhs.getAngle();
        mSpeed = rhs.getSpeed();
        mLife = rhs.getLife();
        mId = rhs.getId();
        mType = rhs.getType();
    }
    return *this;
}

void NGame::Component::setX(double x) { 
    mX = x; 
}

void NGame::Component::setY(double y) { 
    mY = y; 
}

void NGame::Component::setWidth(double width) { 
    mWidth = width; 
}

void NGame::Component::setHeight(double height) { 
    mHeight = height; 
}

void NGame::Component::setAngle(short angle) { 
    mAngle = angle; 
}

void NGame::Component::setSpeed(double speed) { 
    mSpeed = speed; 
}

void NGame::Component::setLife(double life) { 
    mLife = life; 
}

void NGame::Component::setId(uint64_t id) { 
    mId = id; 
}

void NGame::Component::setType(IResource::Type type) { 
    mType = type; 
}

double NGame::Component::getX(void) const { 
    return mX; 
}
double NGame::Component::getY(void) const { 
    return mY; 
}

double NGame::Component::getWidth(void) const { 
    return mWidth; 
}

double NGame::Component::getHeight(void) const { 
    return mHeight; 
}

short NGame::Component::getAngle(void) const { 
    return mAngle; 
}

double NGame::Component::getSpeed(void) const { 
    return mSpeed; 
}

double NGame::Component::getLife(void) const { 
    return mLife; 
}

uint64_t NGame::Component::getId(void) const { 
    return mId; 
}

IResource::Type NGame::Component::getType(void) const { 
    return mType; 
}
