#include "Component.hpp"
#include "PortabilityBuilder.hpp"
#ifdef __OS_LINUX__
# include <math.h>
#endif

NGame::Component::Component(uint64_t id) : mToBeRemoved(false), mId(id), mTime(2500), mType(IResource::Type::UNKNOWN), mDynLib(PortabilityBuilder::getDynLib()) {

}

bool NGame::Component::canFire(void) {
    if (mType != IResource::Type::CASTER && mType != IResource::Type::SUPER && mType != IResource::Type::PLAYER)
        return false;

    if (mFireTimer.getDelta() / 1E6f > mFireDeltaTime) {
        mFireTimer.restart();
        return true;
    }
    return false;
}

bool NGame::Component::canMove(void) const {
    return mMoveTimer.getDelta() > mTime;
}

void NGame::Component::updatePositions(void) {
    float angleInRad = mAngle * 3.14f / 180.f;
    float deltaTime = mType != IResource::Type::PLAYER ? (mMoveTimer.getDelta() / static_cast<float>(mTime)) : 1;
    float dx = mMoveSpeed * cos(angleInRad) * deltaTime;
    float dy = mMoveSpeed * sin(angleInRad) * deltaTime;

    mX += dx;
    mY += dy;

    mMoveTimer.restart();
}

bool NGame::Component::intersect(const std::shared_ptr<NGame::Component>& rhs) const {

    auto c1_left = this->getX();
    auto c2_left = rhs->getX();

    auto c1_right = c1_left + this->getWidth();
    auto c2_right = c2_left + rhs->getWidth();

    auto c1_top = this->getY();
    auto c2_top = rhs->getY();

    auto c1_bot = c1_top + this->getHeight();
    auto c2_bot = c2_top + rhs->getHeight();

    if (c1_right >= c2_left && c1_right <= c2_right && c1_bot >= c2_top && c1_bot <= c2_bot)
        return true;

    if (c1_right >= c2_left && c1_right <= c2_right && c1_top >= c2_top && c1_top <= c2_bot)
        return true;

    if (c1_left >= c2_left && c1_left <= c2_right && c1_bot >= c2_top && c1_bot <= c2_bot)
        return true;

    if (c1_left >= c2_left && c1_left <= c2_right && c1_top >= c2_top && c1_top <= c2_bot)
        return true;

    return false;
}

bool NGame::Component::getToBeRemoved(void) const {
    return mToBeRemoved;
}

void NGame::Component::setToBeRemoved(bool have) {
    mToBeRemoved = have;
}

void NGame::Component::setX(float x) {
    mX = x;
}

void NGame::Component::setY(float y) {
    mY = y;
}

void NGame::Component::setWidth(float width) {
    mWidth = width;
}

void NGame::Component::setHeight(float height) {
    mHeight = height;
}

void NGame::Component::setAngle(float angle) {
    mAngle = angle;
}

void NGame::Component::setMoveSpeed(float moveSpeed) {
    mMoveSpeed = moveSpeed;
}

void NGame::Component::setFireDeltaTime(float fireDeltaTime) {
    mFireDeltaTime = fireDeltaTime;
}

void NGame::Component::setLife(short life) {
    mLife = life;
}

void NGame::Component::setId(uint64_t id) {
    mId = id;
}

void NGame::Component::setType(IResource::Type type) {
    mType = type;
}

void NGame::Component::setOwner(std::shared_ptr<NGame::User>& owner) {
    mOwner = owner;
}

void NGame::Component::setResource(IResource* resource) {
    mResource = resource;
}

float NGame::Component::getX(void) const {
    return mX;
}
float NGame::Component::getY(void) const {
    return mY;
}

float NGame::Component::getWidth(void) const {
    return mWidth;
}

float NGame::Component::getHeight(void) const {
    return mHeight;
}

float NGame::Component::getAngle(void) const {
    return mAngle;
}

float NGame::Component::getMoveSpeed(void) const {
    return mMoveSpeed;
}

float NGame::Component::getFireDeltaTime(void) const {
    return mFireDeltaTime;
}

short NGame::Component::getLife(void) const {
    return mLife;
}

uint64_t NGame::Component::getId(void) const {
    return mId;
}

IResource::Type NGame::Component::getType(void) const {
    return mType;
}

std::shared_ptr<NGame::User>& NGame::Component::getOwner(void) {
    return mOwner;
}

IResource* NGame::Component::getResource(void) const {
    return mResource;
}

const std::shared_ptr<IDynLib> &NGame::Component::getDynLib(void) const {
    return mDynLib;
}
