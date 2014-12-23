#include "Properties.hpp"

NGame::Properties::Properties(void) : mName(""), mLevelName(""), mNbPlayers(0), mNbMaxPlayers(0), mNbSpectators(0), mNbMaxSpectators(0) { 

}

void NGame::Properties::setName(const std::string& name) { 
    mName = name; 
}

void NGame::Properties::setLevelName(const std::string& levelName) { 
    mLevelName = levelName; 
}

void NGame::Properties::setNbPlayers(int nbPlayers) { 
    mNbPlayers = nbPlayers; 
}

void NGame::Properties::setNbMaxPlayers(int nbPlayers) { 
    mNbMaxPlayers = nbPlayers; 
}

void NGame::Properties::setNbSpectators(int nbSpectators) { 
    mNbSpectators = nbSpectators; 
}

void NGame::Properties::setNbMaxSpectators(int nbSpectators) { 
    mNbMaxSpectators = nbSpectators; 
}

const std::string& NGame::Properties::getName(void) const { 
    return mName; 
}

const std::string& NGame::Properties::getLevelName(void) const { 
    return mLevelName; 
}

int NGame::Properties::getNbPlayers(void) const { 
    return mNbPlayers; 
}

int NGame::Properties::getMaxPlayers(void) const { 
    return mNbMaxPlayers; 
}

int NGame::Properties::getNbSpectators(void) const { 
    return mNbSpectators; 
}

int NGame::Properties::getMaxSpectators(void) const { 
    return mNbMaxSpectators; 
}
