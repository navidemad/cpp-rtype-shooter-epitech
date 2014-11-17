#pragma once

#include "IResource.hpp" // créer un fichier IResource.hpp (à la fois dans le client et dans le serveur)
                         // ce fichier contiendra la déclaration des enums IResource::Direction et IResource::Type
#include "ICommand.hpp"

class CommandMove : public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromClient {
			char direction;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandMove(void);
		~CommandMove(void);

	// copy / move operators
	public:
		CommandMove(const CommandMove &) = delete;
		CommandMove(const CommandMove &&) = delete;
		const CommandMove &operator=(const CommandMove &) = delete;
		const CommandMove &operator=(const CommandMove &&) = delete;

	// getter - setters
	public:
		IResource::Direction getDirection(void) const;
		void setDirection(IResource::Direction direction);

	// public pure methods
	public:
		ICommand::Instruction		getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int						getSizeToRead(void) const;
		void										initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		IResource::Direction mDirection;

};
