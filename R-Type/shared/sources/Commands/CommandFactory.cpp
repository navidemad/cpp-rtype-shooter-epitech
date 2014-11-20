#include "CommandFactory.hpp"
#include "CommandError.hpp"
#include "CommandCreateGame.hpp"
#include "CommandJoinGame.hpp"
#include "CommandShowGame.hpp"
#include "CommandDeleteGame.hpp"
#include "CommandListGames.hpp"
#include "CommandUpdatePseudo.hpp"
#include "CommandDisconnect.hpp"
#include "CommandMove.hpp"
#include "CommandFire.hpp"
#include "CommandHandshake.hpp"
#include "CommandEndGame.hpp"
#include "CommandMoveResource.hpp"
#include "CommandDestroyResource.hpp"
#include "CommandObserveGame.hpp"
#include "CommandLeaveGame.hpp"
#include "CommandListLevels.hpp"
#include "CommandShowLevel.hpp"
#include "CommandUpdateScore.hpp"
#include "CommandTimeElapsedPing.hpp"

std::shared_ptr<ICommand> CommandFactory::getCommand(ICommand::Instruction instructionCode) {
	switch (instructionCode) {
	case ICommand::Instruction::ERROR:
		return getCommand<CommandError>();
	case ICommand::Instruction::CREATE_GAME:
		return getCommand<CommandCreateGame>();
	case ICommand::Instruction::JOIN_GAME:
		return getCommand<CommandJoinGame>();
	case ICommand::Instruction::SHOW_GAME:
		return getCommand<CommandJoinGame>();
	case ICommand::Instruction::DELETE_GAME:
		return getCommand<CommandDeleteGame>();
	case ICommand::Instruction::LIST_GAMES:
		return getCommand<CommandListGames>();
	case ICommand::Instruction::UPDATE_PSEUDO:
		return getCommand<CommandUpdatePseudo>();
	case ICommand::Instruction::DISCONNECT:
		return getCommand<CommandDisconnect>();
	case ICommand::Instruction::MOVE:
		return getCommand<CommandMove>();
	case ICommand::Instruction::FIRE:
		return getCommand<CommandFire>();
	case ICommand::Instruction::HANDSHAKE:
		return getCommand<CommandHandshake>();
	case ICommand::Instruction::END_GAME:
		return getCommand<CommandEndGame>();
	case ICommand::Instruction::MOVE_RESOURCE:
		return getCommand<CommandMoveResource>();
	case ICommand::Instruction::DESTROY_RESOURCE:
		return getCommand<CommandDestroyResource>();
	case ICommand::Instruction::OBSERVE_GAME:
		return getCommand<CommandObserveGame>();
	case ICommand::Instruction::LEAVE_GAME:
		return getCommand<CommandLeaveGame>();
	case ICommand::Instruction::LIST_LEVELS:
		return getCommand<CommandListLevels>();
	case ICommand::Instruction::SHOW_LEVEL:
		return getCommand<CommandShowLevel>();
	case ICommand::Instruction::UPDATE_SCORE:
		return getCommand<CommandUpdateScore>();
	case ICommand::Instruction::TIME_ELAPSED_PING:
		return getCommand<CommandTimeElapsedPing>();
	default:
		return nullptr;
	}
}
