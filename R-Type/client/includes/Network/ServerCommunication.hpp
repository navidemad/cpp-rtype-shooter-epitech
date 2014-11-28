#pragma once
#include <list>
#include "IClientSocket.hpp"
#include "ICommand.hpp"
#include "Network/CommandPacketBuilder.hpp"

class ServerCommunication : public CommandPacketBuilder::OnCommandEvent {

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

    //callback from CommandPacketBuilder
    public:
        void    onNewCommand(ICommand *command);

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
        CommandPacketBuilder mHandleTcpCmd;
        int mPortTcp;
        std::string mIpTcp;
        IClientSocket *mSocketTcp;
};
