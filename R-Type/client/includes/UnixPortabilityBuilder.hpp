#pragma once

#include "IReaddir.hpp"

#include <memory>

namespace PortabilityBuilder {

    std::shared_ptr<IReaddir>		getReaddir(void);

}
