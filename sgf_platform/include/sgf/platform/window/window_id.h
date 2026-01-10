#pragma once

#include <sgf/utils/resource_id.h>

namespace sgf_core {
    struct WindowTag {
        static const std::string TypeName;
    };
    using WindowId = ResourceId<WindowTag>;
}
