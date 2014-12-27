#pragma once

#include "IResource.hpp"
#include "ICommand.hpp"
#include "NoCopyable.hpp"

class CommandMoveResource : public NoCopyable, public ICommand {

	// data structs
	public:
		#pragma pack(push, 1)
		struct PacketFromServer {
			uint64_t	id;
			char		type;
            float		x;
            float		y;
            float		angle;
		};
		#pragma pack(pop)

	// ctor / dtor
	public:
		CommandMoveResource(void);
		~CommandMoveResource(void);

	// getter - setters
	public:
		uint64_t 					getId(void) const;
		IResource::Type				getType(void) const;
        float						getX(void) const;
        float						getY(void) const;
        float						getAngle(void) const;

		void	setId(uint64_t id);
		void	setType(IResource::Type type);
        void	setX(float x);
        void	setY(float y);
        void	setAngle(float angle);

	// public pure methods
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// attributes
	private:
		uint64_t		mId;
		IResource::Type mType;
        float			mX;
        float			mY;
        float			mAngle;

};
