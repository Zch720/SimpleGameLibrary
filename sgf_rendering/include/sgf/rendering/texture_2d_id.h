#pragma once

#include <sgf/utils/resource_id.h>

namespace sgf_core {
    struct Texture2DTag {
        static const std::string TypeName;
    };
    using Texture2DId = ResourceId<Texture2DTag>;
}
