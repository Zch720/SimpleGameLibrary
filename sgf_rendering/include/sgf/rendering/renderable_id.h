#pragma once

#include <sgf/utils/resource_id.h>

namespace sgf_core {
    struct RenderableTag {
        static const std::string TypeName;
    };
    using RenderableId = ResourceId<RenderableTag>;
}
