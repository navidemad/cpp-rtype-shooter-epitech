#pragma once

#include <memory>

#include "IDynLib.hpp"

namespace PortabilityBuilder {

    std::shared_ptr<IDynLib> getDynLib(void);

}
