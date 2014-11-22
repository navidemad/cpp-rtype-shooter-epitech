#include "Client.hpp"

const Client::CommandExec Client::commandExecTab[] = {
	{ ICommand::Instruction::CREATE_GAME,	&Client::recvCreateGame		},
	{ ICommand::Instruction::JOIN_GAME,		&Client::recvJoinGame		},
	{ ICommand::Instruction::SHOW_GAME,		&Client::recvShowGame		},
	{ ICommand::Instruction::DELETE_GAME,	&Client::recvDeleteGame		},
	{ ICommand::Instruction::LIST_GAMES,	&Client::recvListGames		},
	{ ICommand::Instruction::LIST_LEVELS,	&Client::recvListLevels		},
	{ ICommand::Instruction::DISCONNECT,	&Client::recvDisconnect		},
	{ ICommand::Instruction::HANDSHAKE,		&Client::recvHandshake		},
	{ ICommand::Instruction::OBSERVE_GAME,	&Client::recvObserveGame	},
	{ ICommand::Instruction::LEAVE_GAME,	&Client::recvLeaveGame		},
	{ ICommand::Instruction::UPDATE_PSEUDO, &Client::recvUpdatePseudo	},
	{ ICommand::Instruction::UNKNOWN,		nullptr						}
};

Client::Client(const std::shared_ptr<IClientSocket> &client) : mListener(nullptr), mClientPacketBuilder(client) {
	mClientPacketBuilder.setListener(this);
}

Client::~Client(void) {
}

void	Client::onPacketAvailable(const ClientPacketBuilder &, const std::shared_ptr<ICommand> &command) {
	for (const auto &cmdExec : commandExecTab)
		if (cmdExec.instruction == command->getInstruction()) {
			(this->*cmdExec.ftPtr)(command);
			break;
		}
}

void	Client::onSocketClosed(const ClientPacketBuilder &) {
	if (mListener)
		mListener->onClientDisconnected(*this);
}

void	Client::setListener(Client::OnClientEvent *listener) {
	mListener = listener;
}

void	Client::recvCreateGame(const std::shared_ptr<ICommand> &command) {
}

void	Client::recvJoinGame(const std::shared_ptr<ICommand> &command) {
}

void	Client::recvShowGame(const std::shared_ptr<ICommand> &command) {
}

void	Client::recvDeleteGame(const std::shared_ptr<ICommand> &command) {
}

void	Client::recvListGames(const std::shared_ptr<ICommand> &command) {
}

void	Client::recvListLevels(const std::shared_ptr<ICommand> &command) {
}

void	Client::recvDisconnect(const std::shared_ptr<ICommand> &command) {
}

void	Client::recvHandshake(const std::shared_ptr<ICommand> &command) {
}

void	Client::recvObserveGame(const std::shared_ptr<ICommand> &command) {
}

void	Client::recvLeaveGame(const std::shared_ptr<ICommand> &command) {
}

void	Client::recvUpdatePseudo(const std::shared_ptr<ICommand> &command) {
}
