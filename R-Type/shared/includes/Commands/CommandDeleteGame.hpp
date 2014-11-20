#pragma once

#include <string>
#include "ICommand.hpp"

class CommandDeleteGame : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
			char	name[64];
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandDeleteGame(void);
		~CommandDeleteGame(void);

	// copy / move operators
	public:
		CommandDeleteGame(const CommandDeleteGame &) = delete;
		CommandDeleteGame(const CommandDeleteGame &&) = delete;
		const CommandDeleteGame &operator=(const CommandDeleteGame &) = delete;
		const CommandDeleteGame &operator=(const CommandDeleteGame &&) = delete;

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
		std::string	mName;

};
