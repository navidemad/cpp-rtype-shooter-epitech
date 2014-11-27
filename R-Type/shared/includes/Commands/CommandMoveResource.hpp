#pragma once

#include "IResource.hpp"
#include "ICommand.hpp"
#include "NoCopyable.hpp"

class CommandMoveResource : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			int32_t	id;
			char		type;
			float		x;
			float		y;
			short		angle;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		explicit CommandMoveResource(void);
		~CommandMoveResource(void);

	// getter - setters
	public:
		int 						getId(void) const;
		IResource::Type getType(void) const;
		float						getX(void) const;
		float						getY(void) const;
		short						getAngle(void) const;

		void	setId(int id);
		void	setType(IResource::Type type);
		void	setX(float x);
		void	setY(float y);
		void	setAngle(short angle);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		int 			mId;
		IResource::Type mType;
		float			mX;
		float			mY;
		short			mAngle;

};
