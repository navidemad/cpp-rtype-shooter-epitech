#pragma once

#include <string>
#include "ICommand.hpp"

class CommandJoinGame : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
			char	name[64];
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		explicit CommandJoinGame(void);
		~CommandJoinGame(void);

	// copy / move operators
	public:
		CommandJoinGame(const CommandJoinGame &) = delete;
		CommandJoinGame(CommandJoinGame &&) = delete;
		const CommandJoinGame &operator=(const CommandJoinGame &) = delete;
		const CommandJoinGame &operator=(CommandJoinGame &&) = delete;

	// getter - setters
	public:
		const std::string &getName(void) const;
		void setName(const std::string &name);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		std::string mName;

};
