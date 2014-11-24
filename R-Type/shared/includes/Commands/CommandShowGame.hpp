#pragma once

#include <string>
#include "ICommand.hpp"

class CommandShowGame : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			char	name[64];
			char	levelName[64];
			char	nbPlayers;
			char	maxPlayers;
			char	nbObservers;
			char	maxObservers;
		};
		#pragma pack(pop)

		#pragma pack(push, 1)
		struct PacketFromClient {
			char	name[64];
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		explicit CommandShowGame(void);
		~CommandShowGame(void);

	// copy / move operators
	public:
		CommandShowGame(const CommandShowGame &) = delete;
		CommandShowGame(CommandShowGame &&) = delete;
		const CommandShowGame &operator=(const CommandShowGame &) = delete;
		const CommandShowGame &operator=(CommandShowGame &&) = delete;

	// getter - setters
	public:
		const std::string &getName(void) const;
		const std::string &getLevelName(void) const;
		char getNbPlayers(void) const;
		char getMaxPlayers(void) const;
		char getNbObservers(void) const;
		char getMaxObservers(void) const;

		void setName(const std::string &name);
		void setLevelName(const std::string &levelName);
		void setNbPlayers(char nbPlayers);
		void setMaxPlayers(char maxPlayers);
		void setNbObservers(char nbObservers);
		void setMaxObservers(char maxObservers);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		std::string mName;
		std::string	mLevelName;
		char		mNbPlayers;
		char		mMaxPlayers;
		char		mNbObservers;
		char		mMaxObservers;

};
