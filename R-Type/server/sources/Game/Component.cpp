#include "Component.hpp"
#include "PortabilityBuilder.hpp"

NGame::Component::Component(uint64_t id) : mId(id), mType(IResource::Type::UNKNOWN), mDynLib(PortabilityBuilder::getDynLib()) {

}

bool NGame::Component::canFire(void) {
    if (mFireTimer.getDelta() / 1E3 > getFireDeltaTime()) {
        mFireTimer.restart();
        return true;
    }
    return false;
}

bool NGame::Component::intersect(const std::shared_ptr<NGame::Component>& rhs) const {
    auto c1_top = mY - mHeight / 2;
    auto c1_bottom = mY + mHeight / 2;
    auto c1_left = mX - mWidth / 2;
    auto c1_right = mX + mWidth / 2;

    auto c2_top = rhs->getY() - rhs->getHeight() / 2;
    auto c2_bottom = rhs->getY() + rhs->getHeight() / 2;
    auto c2_left = rhs->getX() - rhs->getWidth() / 2;
    auto c2_right = rhs->getX() + rhs->getWidth() / 2;

    return !((c1_bottom > c2_top) || (c1_top < c2_bottom) || (c1_left > c2_right) || (c1_right < c2_left));
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

void NGame::Component::setFireDeltaTime(double fireDeltaTime) {
    mFireDeltaTime = fireDeltaTime;
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

double NGame::Component::getFireDeltaTime(void) const {
    return mFireDeltaTime;
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

const std::shared_ptr<IDynLib> &NGame::Component::getDynLib(void) const {
    return mDynLib;
}
