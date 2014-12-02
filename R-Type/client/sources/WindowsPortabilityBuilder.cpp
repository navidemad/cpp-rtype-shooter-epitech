#include "PortabilityBuilder.hpp"

# include "WindowsReaddir.hpp"

std::shared_ptr<IReaddir> PortabilityBuilder::getReaddir(void) {
	return std::make_shared<WindowsReaddir>();
}
