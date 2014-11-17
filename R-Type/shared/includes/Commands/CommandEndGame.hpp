#pragma once

#include <string>
#include "ICommand.hpp"

class CommandEndGame : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			char	name[64];
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandEndGame(void);
		~CommandEndGame(void);

	// copy / move operators
	public:
		CommandEndGame(const CommandEndGame &) = delete;
		CommandEndGame(const CommandEndGame &&) = delete;
		const CommandEndGame &operator=(const CommandEndGame &) = delete;
		const CommandEndGame &operator=(const CommandEndGame &&) = delete;

	// getter - setters
	public:
		const std::string &getName(void) const;
		void setName(const std::string &name);

	// public pure methods
	public:
		ICommand::Instruction		getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int						getSizeToRead(void) const;
		void										initFromMessage(const IClientSocket::Message &message);

	//attributes
	private:
		std::string	mName;

};
