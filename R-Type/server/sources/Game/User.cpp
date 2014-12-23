#include "User.hpp"

NGame::User::User(const NGame::User& rhs) {
    if (this != &rhs) {
        mPeer = rhs.getPeer();
        mPseudo = rhs.getPseudo();
        mType = rhs.getType();
        mUserId = rhs.getId();
        mScore = rhs.getScore();
    }
}

NGame::User& NGame::User::operator = (const NGame::User& rhs) {
    if (this != &rhs) {
        mPeer = rhs.getPeer();
        mPseudo = rhs.getPseudo();
        mType = rhs.getType();
        mUserId = rhs.getId();
        mScore = rhs.getScore();
    }
    return *this;
}

void NGame::User::setPeer(const Peer &peer) { 
    mPeer = peer;
}

void NGame::User::setPseudo(const std::string& pseudo) { 
    mPseudo = pseudo; 
}

void NGame::User::setType(NGame::USER_TYPE type) { 
    mType = type; 
}

void NGame::User::setId(uint64_t id) { 
    mUserId = id; 
}

void NGame::User::setScore(uint64_t score) { 
    mScore = score; 
}

const Peer& NGame::User::getPeer(void) const { 
    return mPeer; 
}

const std::string& NGame::User::getPseudo(void) const { 
    return mPseudo; 
}

NGame::USER_TYPE NGame::User::getType(void) const { 
    return mType; 
}

uint64_t NGame::User::getId(void) const { 
    return mUserId; 
}

uint64_t NGame::User::getScore(void) const { 
    return mScore; 
}
