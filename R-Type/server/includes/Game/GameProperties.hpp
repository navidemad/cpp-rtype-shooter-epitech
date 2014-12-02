#pragma once

#include <string>

namespace NGame
{

    class Properties {

        // ctor / dtor
        public:
            Properties(void) : mName(""), mLevelName(""), mNbPlayers(0), mNbMaxPlayers(0), mNbSpectators(0), mNbMaxSpectators(0) { }
            ~Properties(void) { }

        // setters
        public:
            void setName(const std::string& name) { mName = name; }
            void setLevelName(const std::string& levelName) { mLevelName = levelName; }
            void setNbPlayers(int nbPlayers) { mNbPlayers = nbPlayers; }
            void setNbMaxPlayers(int nbPlayers) { mNbMaxPlayers = nbPlayers; }
            void setNbSpectators(int nbSpectators) { mNbSpectators = nbSpectators; }
            void setNbMaxSpectators(int nbSpectators) { mNbMaxSpectators = nbSpectators; }

        // getters
        public:
            const std::string& getName(void) const { return mName; }
            const std::string& getLevelName(void) const { return mLevelName; }
            int getNbPlayers(void) const { return mNbPlayers; }
            int getMaxPlayers(void) const { return mNbMaxPlayers; }
            int getNbSpectators(void) const { return mNbSpectators; }
            int getMaxSpectators(void) const { return mNbMaxSpectators; }

        // attributes
        private:
            std::string mName;
            std::string mLevelName;
            int mNbPlayers;
            int mNbMaxPlayers;
            int mNbSpectators;
            int mNbMaxSpectators;

    };

}