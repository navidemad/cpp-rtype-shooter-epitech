#include "PortabilityBuilder.hpp"

# include "UnixDynLib.hpp"

std::shared_ptr<IDynLib> PortabilityBuilder::getDynLib(void) {
    return std::make_shared<UnixDynLib>();
}
