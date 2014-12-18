#pragma once

#include "IDynLib.hpp"

#include <memory>

namespace PortabilityBuilder {

    std::shared_ptr<IDynLib> getDynLib(void);

}
