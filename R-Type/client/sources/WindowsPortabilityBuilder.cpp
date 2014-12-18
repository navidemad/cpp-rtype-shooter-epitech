#include "PortabilityBuilder.hpp"

# include "WindowsDynLib.hpp"

std::shared_ptr<IDynLib> PortabilityBuilder::getDynLib(void) {
    return std::make_shared<WindowsDynLib>();
}
