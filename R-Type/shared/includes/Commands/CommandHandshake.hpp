#pragma once

#include "ICommand.hpp"
#include "NoCopyable.hpp"

class CommandHandshake : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			int udpPort;
		};
		#pragma pack(pop)

		#pragma pack(push, 1)
		struct PacketFromClient {
			int udpPort;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandHandshake(void);
		~CommandHandshake(void);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// getter setter
	public:
		int getUdpPort(void) const;
		void setUdpPort(int udpPort);

	// attributes
	private:
		int mUdpPort;

};
