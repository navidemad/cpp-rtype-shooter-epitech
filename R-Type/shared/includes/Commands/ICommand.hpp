#pragma once

#include "IClientSocket.hpp"

#include <cstdint>

class ICommand {

	// Instructions
	public:
		enum class Instruction {
			ERROR 				= 0x00,
			CREATE_GAME 		= 0x01,
			JOIN_GAME 			= 0x02,
			SHOW_GAME 			= 0x03,
			DELETE_GAME 		= 0x04,
			LIST_GAMES 			= 0x05,
			UPDATE_PSEUDO 		= 0x06,
			MOVE 				= 0x08,
			FIRE 				= 0x09,
			HANDSHAKE 			= 0x0A,
			END_GAME 			= 0x0B,
			MOVE_RESOURCE 		= 0x0C,
			DESTROY_RESOURCE 	= 0x0D,
			OBSERVE_GAME 		= 0x0E,
			LEAVE_GAME 			= 0x0F,
			LIST_LEVELS 		= 0x10,
			SHOW_LEVEL 			= 0x11,
			UPDATE_SCORE 		= 0x12,
			TIME_ELAPSED_PING	= 0x13,
			UNKNOWN
		};

	// header
	public:
		static const int32_t		MAGIC_CODE;
		static const unsigned int	HEADER_SIZE;

		#pragma pack(push, 1)
		struct Header {
			int32_t	magicCode;
			int32_t	instructionCode;
		};
		#pragma pack(pop)

	// virtual destructor
	public:
		virtual ~ICommand(void) {}

	// public pure methods
	public:
		virtual ICommand::Instruction	getInstruction(void) const = 0;
		virtual	IClientSocket::Message	getMessage(void) const = 0;
		virtual unsigned int			getSizeToRead(void) const = 0;
		virtual void					initFromMessage(const IClientSocket::Message &message) = 0;

};
