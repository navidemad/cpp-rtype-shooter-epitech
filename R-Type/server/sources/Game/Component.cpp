#include "Component.hpp"
#include "PortabilityBuilder.hpp"

NGame::Component::Component(uint64_t id) : 
    last_move(std::chrono::high_resolution_clock::now()),
    last_fire(std::chrono::high_resolution_clock::now()),
    mId(id),
    mType(IResource::Type::UNKNOWN),mDynLib(PortabilityBuilder::getDynLib())
{

}

NGame::Component::Component(const NGame::Component& rhs) {
    if (this != &rhs)
        deepCopy(rhs);
}
NGame::Component& NGame::Component::operator = (const NGame::Component& rhs) {
    if (this != &rhs)
        deepCopy(rhs);
    return *this;
}

void NGame::Component::deepCopy(const NGame::Component& rhs) {
    mX = rhs.getX();
    mY = rhs.getY();
    mWidth = rhs.getWidth();
    mHeight = rhs.getHeight();
    mAngle = rhs.getAngle();
    mMoveSpeed = rhs.getMoveSpeed();
    mFireSpeed = rhs.getFireSpeed();
    mLife = rhs.getLife();
    mId = rhs.getId();
    mType = rhs.getType();
    mOwnerId = rhs.getOwnerId();
    mDynLib = rhs.getDynLib();
}

bool NGame::Component::canMove(void) {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration_in_sec = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_move).count();
    if (duration_in_sec > 20) // getMoveSpeed() milliseconds
    {
        last_move = now;
        return true;
    }
    return false;
}

bool NGame::Component::canFire(void) {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration_in_sec = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_fire).count();
    if (duration_in_sec > 20) // getFireSpeed() milliseconds
    {
        last_fire = now;
        return true;
    }
    return false;
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

void NGame::Component::setMoveSpeed(double moveSpeed) { 
    mMoveSpeed = moveSpeed;
}

void NGame::Component::setFireSpeed(double fireSpeed) {
    mFireSpeed = fireSpeed;
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

void NGame::Component::setOwnerId(uint64_t ownerId) {
    mOwnerId = ownerId;
}

void NGame::Component::setResource(IResource* resource) {
    mResource = resource;
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

double NGame::Component::getMoveSpeed(void) const { 
    return mMoveSpeed; 
}

double NGame::Component::getFireSpeed(void) const {
    return mFireSpeed;
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

uint64_t NGame::Component::getOwnerId(void) const {
    return mOwnerId;
}

IResource* NGame::Component::getResource(void) const {
    return mResource;
}

std::shared_ptr<IDynLib> NGame::Component::getDynLib(void) const {
    return mDynLib;
}
