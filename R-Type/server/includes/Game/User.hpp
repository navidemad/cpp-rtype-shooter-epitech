#pragma once

#include "Peer.hpp"
#include "NGame.hpp"

#include <string>
#include <cstdint>
#include <iostream>

namespace NGame
{

    class User {

        // ctor / dtor / copy / operator=
        public:
			User(void) = default;
			~User(void) = default;
            User(const User& rhs);
            User& operator=(const User& rhs);

        // setters
        public:
            void setPeer(const Peer &peer);
            void setPseudo(const std::string& pseudo);
            void setType(NGame::USER_TYPE type);
            void setId(uint64_t id);
            void setScore(uint64_t score);

        // getters
        public:
            const Peer& getPeer(void) const;
            const std::string& getPseudo(void) const;
            NGame::USER_TYPE getType(void) const;
            uint64_t getId(void) const;
            uint64_t getScore(void) const;

        // attributes
        private:
            Peer mPeer;
            std::string mPseudo;
            NGame::USER_TYPE mType;
            uint64_t mUserId;
			uint64_t mScore;

    };

}
