#pragma once
#include <list>
#include "IClientSocket.hpp"
#include "ICommand.hpp"
#include "ClientPacketBuilder.hpp"
#include "PlayerPacketBuilder.hpp"
#include "IResource.hpp"
#include "ErrorStatus.hpp"
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


    //serverComunication's callback
    public:
        class OnServerEvent {
            public:
                virtual ~OnServerEvent(void) {}
                virtual void OnDestroyResource(int id) = 0;
                virtual void OnEndGame(const std::string &name) = 0;
                virtual void OnError(ICommand::Instruction instruction, ErrorStatus::Error) = 0;
                virtual void OnMoveResource(IResource::Type type, float x, float y, short angle, int id) = 0;
                virtual void OnShowGame(const std::string &name, const std::string &levelName, int nbPlayer, int maxPlayer, int nbObserver, int maxObserver) = 0;
                virtual void OnShowLevel(const std::string &name, const std::string &script) = 0;
                virtual void OnTimeElapse(int64_t time) = 0;
                virtual void OnUpdateScore(const std::string &name, int id, int score) = 0;
        };

    //handle command from server
    public:
        struct HandleServerCommand {
            ICommand::Instruction key;
            void (ServerCommunication::*fct)(ICommand *command);
        };
        static const ServerCommunication::HandleServerCommand tabHandleServerCommand[];

        void ExecServerCommand(ICommand *command);
        void ExecDestroyResource(ICommand *command);
        void ExecEndGame(ICommand *command);
        void ExecError(ICommand *command);
        void ExecMoveResource(ICommand *command);
        void ExecShowGame(ICommand *command);
        void ExecShowLevel(ICommand *command);
        void ExecTimeElapse(ICommand *command);
        void ExecUpdateScore(ICommand *command);
        void ExecHandShake(ICommand *command);

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
        OnServerEvent *mListenerEcs;
};
