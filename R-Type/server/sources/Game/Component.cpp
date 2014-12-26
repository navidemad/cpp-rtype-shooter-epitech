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
