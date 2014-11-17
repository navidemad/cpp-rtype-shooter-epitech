#pragma once

#include "ICommand.hpp"

class CommandTimeElapsedPing : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			int64_t	timeElapsed;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandTimeElapsedPing(void);
		~CommandTimeElapsedPing(void);

	// copy / move operators
	public:
		CommandTimeElapsedPing(const CommandTimeElapsedPing &) = delete;
		CommandTimeElapsedPing(const CommandTimeElapsedPing &&) = delete;
		const CommandTimeElapsedPing &operator=(const CommandTimeElapsedPing &) = delete;
		const CommandTimeElapsedPing &operator=(const CommandTimeElapsedPing &&) = delete;

	// getter - setters
	public:
		int64_t getTimeElapsed(void) const;
		void		setTimeElapsed(int64_t timeElapsed);

	// public pure methods
	public:
		ICommand::Instruction		getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int						getSizeToRead(void) const;
		void										initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		int64_t mTimeElapsed;

};
