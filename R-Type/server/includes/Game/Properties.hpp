#pragma once

#include <string>

namespace NGame
{

    class Properties {

        // ctor / dtor
        public:
            Properties(void);
            ~Properties(void) = default;

        // setters
        public:
            void setName(const std::string& name);
            void setLevelName(const std::string& levelName);
            void setNbPlayers(int nbPlayers);
            void setNbMaxPlayers(int nbPlayers);
            void setNbSpectators(int nbSpectators);
            void setNbMaxSpectators(int nbSpectators);

        // getters
        public:
            const std::string& getName(void) const;
            const std::string& getLevelName(void) const;
            int getNbPlayers(void) const;
            int getMaxPlayers(void) const;
            int getNbSpectators(void) const;
            int getMaxSpectators(void) const;

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