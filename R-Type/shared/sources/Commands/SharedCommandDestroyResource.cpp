#include "CommandDestroyResource.hpp"

CommandDestroyResource::CommandDestroyResource(void) : mId(0) {
}

CommandDestroyResource::~CommandDestroyResource(void) {
}

int  CommandDestroyResource::getId(void) const {
	return mId;
}

void CommandDestroyResource::setId(int id) {
	mId = id;
}

ICommand::Instruction	CommandDestroyResource::getInstruction(void) const {
	return ICommand::Instruction::DESTROY_RESOURCE;
}
