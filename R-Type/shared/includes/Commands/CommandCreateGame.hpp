#pragma once

#include <string>
#include "ICommand.hpp"

class CommandCreateGame : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
			char	name[64];
			char	levelName[64];
			char	nbPlayers;
			char	nbSpectators;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandCreateGame(void);
		~CommandCreateGame(void);

	// copy / move operators
	public:
		CommandCreateGame(const CommandCreateGame &) = delete;
		CommandCreateGame(const CommandCreateGame &&) = delete;
		const CommandCreateGame &operator=(const CommandCreateGame &) = delete;
		const CommandCreateGame &operator=(const CommandCreateGame &&) = delete;

	// getter - setters
	public:
		const std::string	&getName(void) const;
		const std::string &getLevelName(void) const;
		char getNbPlayers(void) const;
		char getNbSpectators(void) const;

		void setName(const std::string &name);
		void setLevelName(const std::string &levelName);
		void setNbPlayers(char nbPlayers);
		void setNbSpectators(char nbSpectators);

	// public pure methods
	public:
		ICommand::Instruction		getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int						getSizeToRead(void) const;
		void										initFromMessage(const IClientSocket::Message &message);


	// attributes
	private:
		std::string	mName;
		std::string	mLevelName;
		char				mNbPlayers;
		char				mNbSpectators;

};
