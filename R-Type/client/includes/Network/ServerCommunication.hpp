#pragma once
#include <QObject>
#include "IClientSocket.hpp"
#include "ICommand.hpp"
#include "ClientPacketBuilder.hpp"
#include "PlayerPacketBuilder.hpp"
#include "IResource.hpp"
#include "ErrorStatus.hpp"
#include <memory>

class ServerCommunication : public QObject, ClientPacketBuilder::OnClientPacketBuilderEvent, PlayerPacketBuilder::OnPlayerPacketBuilderEvent{
    Q_OBJECT

    // ctor - dtor
    public:
        explicit ServerCommunication(int ClientUdpPort);
        ~ServerCommunication();

    // copy operators
    public:
        ServerCommunication(const ServerCommunication &) = delete;
        ServerCommunication(ServerCommunication &&) = delete;
        const ServerCommunication &operator=(const ServerCommunication &) = delete;
        const ServerCommunication &operator=(ServerCommunication &&) = delete;

    //signal
    signals:
        void SignalDestroyResource(int id);
        void SignalEndGame(const std::string &name);
        void SignalError(ICommand::Instruction instruction, ErrorStatus::Error);
        void SignalMoveResource(IResource::Type type, float x, float y, short angle, int id);
        void SignalShowGame(const std::string &name, const std::string &levelName, int nbPlayer, int maxPlayer, int nbObserver, int maxObserver);
        void SignalShowLevel(const std::string &name, const std::string &script);
        void SignalTimeElapse(int64_t time);
        void SignalUpdateScore(const std::string &name, int id, int score);
        void SignalCloseSocket(void);

    //slots
    public slots:
        void OnCreateGame(const std::string &name, const std::string &levelName, int nbPlayer, int nbObserver);
        void OnDeleteGame(const std::string &name);
        void OnFire(void);
        void OnJoinGame(const std::string &name);
        void OnLeaveGame(void);
        void OnListGame(void);
        void OnListLevel(void);
        void OnMove(IResource::Direction direction);
        void OnObserveGame(const std::string &name);
        void OnShowGame(const std::string &name);
        void OnUpdatePseudo(const std::string &pseudo);
        void OnSetServerIp(const std::string &ip);
        void OnSetServerPortTcp(int port);
        void OnConnectToServer(void);

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

    //dry
    private:
        void sendCommand(ICommand *command, bool isTcpCommand);

    //attribut
    private:
        int mClientPortUdp;
        Peer mServerPeer;
        std::shared_ptr<IClientSocket> mSocketTcp;
        ClientPacketBuilder mCmdTcp;
        PlayerPacketBuilder mCmdUdp;
};
