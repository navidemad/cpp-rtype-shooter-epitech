#pragma once

#include "ICommand.hpp"
#include "NoCopyable.hpp"

class CommandTimeElapsedPing : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			int64_t	timeElapsed;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		explicit CommandTimeElapsedPing(void);
		~CommandTimeElapsedPing(void);

	// getter - setters
	public:
		int64_t getTimeElapsed(void) const;
		void		setTimeElapsed(int64_t timeElapsed);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		int64_t mTimeElapsed;

};
