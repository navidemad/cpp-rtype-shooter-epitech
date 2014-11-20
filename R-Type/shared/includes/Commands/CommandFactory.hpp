#pragma once

#include <memory>
#include "ICommand.hpp"

namespace CommandFactory {

	template<typename T>
	std::shared_ptr<ICommand> getCommand(void) {
		return std::make_shared<T>();
	}

	std::shared_ptr<ICommand> getCommand(ICommand::Instruction instructionCode);

};
