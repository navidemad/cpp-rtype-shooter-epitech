#include "PortabilityBuilder.hpp"

# include "UnixReaddir.hpp"

std::shared_ptr<IReaddir> PortabilityBuilder::getReaddir(void) {
	return std::make_shared<UnixReaddir>();
}
