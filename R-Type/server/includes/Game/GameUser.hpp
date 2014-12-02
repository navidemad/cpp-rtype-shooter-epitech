#pragma once

#include "Peer.hpp"
#include "NGame.hpp"

#include <string>
#include <cstdint>

namespace NGame
{

    class User {

        // ctor / dtor
        public:
            explicit User(void) { }
            ~User(void) { }

        // setters
        public:
            void setPeer(const Peer &peer) { mPeer = peer; }
            void setPseudo(const std::string& pseudo) { mPseudo = pseudo; }
            void setType(NGame::USER_TYPE type) { mType = type; }
            void setId(uint64_t id) { mUserId = id; }

        // getters
        public:
            const Peer& getPeer(void) const { return mPeer; }
            const std::string& getPseudo(void) const { return mPseudo; }
            NGame::USER_TYPE getType(void) const { return mType; }
            uint64_t getId(void) const { return mUserId; }

        // attributes
        private:
            Peer mPeer;
            std::string mPseudo;
            NGame::USER_TYPE mType;
            uint64_t mUserId;

    };

}
