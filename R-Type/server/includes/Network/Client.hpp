#pragma once

#include <memory>
#include "ErrorStatus.hpp"
#include "IClientSocket.hpp"
#include "ClientPacketBuilder.hpp"

class Client : public ClientPacketBuilder::OnClientPacketBuilderEvent {

	// ctor dtor
	public:
		explicit Client(const std::shared_ptr<IClientSocket> &client);
		~Client(void);

	// copy operators
	public:
		Client(const Client &) = delete;
		Client(Client &&) = delete;
		const Client &operator=(const Client &) = delete;
		const Client &operator=(Client &&) = delete;

	// ptr tab
	private:
		struct CommandExec {
			ICommand::Instruction	instruction;
			void					(Client::*ftPtr)(const std::shared_ptr<ICommand> &command);
		};

		static const Client::CommandExec commandExecTab[];

		void	recvCreateGame(const std::shared_ptr<ICommand> &command);
		void	recvJoinGame(const std::shared_ptr<ICommand> &command);
		void	recvShowGame(const std::shared_ptr<ICommand> &command);
		void	recvDeleteGame(const std::shared_ptr<ICommand> &command);
		void	recvListGames(const std::shared_ptr<ICommand> &command);
		void	recvListLevels(const std::shared_ptr<ICommand> &command);
		void	recvDisconnect(const std::shared_ptr<ICommand> &command);
		void	recvHandshake(const std::shared_ptr<ICommand> &command);
		void	recvObserveGame(const std::shared_ptr<ICommand> &command);
		void	recvLeaveGame(const std::shared_ptr<ICommand> &command);
		void	recvUpdatePseudo(const std::shared_ptr<ICommand> &command);

	// events
	public:
		class OnClientEvent {
			public:
				virtual ~OnClientEvent(void) {}
				virtual void	onClientCreateGame(const Client &client, const std::string &name, const std::string &levelName, int nbPlayers, int nbObservers) = 0;
				virtual void	onClientJoinGame(const Client &client, const std::string &name) = 0;
				virtual void	onClientShowGame(const Client &client, const std::string &name) = 0;
				virtual void	onClientDeleteGame(const Client &client, const std::string &name) = 0;
				virtual void	onClientListGames(const Client &client) = 0;
				virtual void	onClientListLevels(const Client &client) = 0;
				virtual void	onClientDisconnect(const Client &client) = 0;
				virtual void	onClientHandshake(Client &client) = 0;
				virtual void	onClientObserveGame(const Client &client, const std::string &name) = 0;
				virtual void	onClientLeaveGame(const Client &client) = 0;
				virtual void	onClientUpdatePseudo(Client &client, const std::string &pseudo) = 0;
				virtual void	onClientDisconnected(const Client &client) = 0;
		};

		void	setListener(Client::OnClientEvent *mListener);
		void	onPacketAvailable(const ClientPacketBuilder &clientPacketBuilder, const std::shared_ptr<ICommand> &command);
		void	onSocketClosed(const ClientPacketBuilder &clientPacketBuilder);

	// send command
	public:
		void	handshake(void);
		void	sendError(const ErrorStatus &errorStatus);
		void	sendShowGame(const std::string &name, const std::string &levelName, int nbPlayers, int maxPlayers, int nbObservers, int maxObservers);
		void	sendEndGame(void);
		void	sendShowLevel(const std::string &name, const std::string &script);

	// getters setters
	public:
		const std::string &getHost(void) const;
		const std::string &getPseudo(void) const;
		bool isAuthenticated(void) const;
		void setIsAuthenticated(bool isAuthenticated);
		void setPseudo(const std::string &pseudo);

	// attributes
	private:
		std::string mHost;
		std::string mPseudo;
		bool mIsAuthenticated;
		Client::OnClientEvent *mListener;
		ClientPacketBuilder mClientPacketBuilder;

};
