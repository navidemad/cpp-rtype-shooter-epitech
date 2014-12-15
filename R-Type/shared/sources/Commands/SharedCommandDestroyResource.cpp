#include "CommandDestroyResource.hpp"

CommandDestroyResource::CommandDestroyResource(void) : mId(0) {
}

CommandDestroyResource::~CommandDestroyResource(void) {
}

uint64_t  CommandDestroyResource::getId(void) const {
	return mId;
}

void CommandDestroyResource::setId(uint64_t id) {
	mId = id;
}

ICommand::Instruction	CommandDestroyResource::getInstruction(void) const {
	return ICommand::Instruction::DESTROY_RESOURCE;
}
