#pragma once

#include "ErrorStatus.hpp"
#include "ICommand.hpp"
#include "NoCopyable.hpp"

class CommandError : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			ICommand::Instruction 	instructionCode;
			ErrorStatus::Error 		errorCode;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		explicit CommandError(void);
		~CommandError(void);

	// getter - setters
	public:
		ICommand::Instruction 	getInstructionCode(void) const;
		ErrorStatus::Error 			getErrorCode(void) const;

		void	setInstructionCode(ICommand::Instruction instruction);
		void	setErrorCode(ErrorStatus::Error error);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		ICommand::Instruction	mInstructionCode;
		ErrorStatus::Error 		mErrorCode;

};
