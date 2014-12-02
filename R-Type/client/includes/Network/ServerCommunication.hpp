#pragma once
#include <list>
#include "IClientSocket.hpp"
#include "ICommand.hpp"
#include "ClientPacketBuilder.hpp"
#include "PlayerPacketBuilder.hpp"
#include <memory>

class ServerCommunication : ClientPacketBuilder::OnClientPacketBuilderEvent, PlayerPacketBuilder::OnPlayerPacketBuilderEvent{

    // ctor - dtor
    public:
        explicit ServerCommunication();
        ~ServerCommunication();

    // copy operators
    public:
        ServerCommunication(const ServerCommunication &) = delete;
        ServerCommunication(ServerCommunication &&) = delete;
        const ServerCommunication &operator=(const ServerCommunication &) = delete;
        const ServerCommunication &operator=(ServerCommunication &&) = delete;

    //callback from ClientPacketBuilder
    public:
        void    onPacketAvailable(const ClientPacketBuilder &clientPacketBuilder, const std::shared_ptr<ICommand> &command);
        void    onSocketClosed(const ClientPacketBuilder &clientPacketBuilder);

    //callback from PlayerPacketBuilder
    public:
        void onPacketAvailable(const PlayerPacketBuilder &clientPacketBuilder, const std::shared_ptr<ICommand> &command, const Peer &peer);

    //handle socket
    public:
        void connectSocketTcp(void);

    //getter
    public:
        std::list<ICommand *> &getCommand(void);

    //setter
    public:
        void setServerTcp(int port, std::string ip);

    //attribut
    private:
        std::list<ICommand *> mListCommand;
        int mPortTcp;
        std::string mIpTcp;
        std::shared_ptr<IClientSocket> mSocketTcp;
        ClientPacketBuilder mCmdTcp;
        PlayerPacketBuilder mCmdUdp;
};
