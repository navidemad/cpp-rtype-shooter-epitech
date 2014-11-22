#pragma once

#include <memory>
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
				virtual void	onClientDisconnected(const Client &) = 0;
		};

		void	setListener(Client::OnClientEvent *mListener);
		void	onPacketAvailable(const ClientPacketBuilder &clientPacketBuilder, const std::shared_ptr<ICommand> &command);
		void	onSocketClosed(const ClientPacketBuilder &clientPacketBuilder);

	// attributes
	private:
		Client::OnClientEvent *mListener;
		ClientPacketBuilder mClientPacketBuilder;

};
