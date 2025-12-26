#pragma once

#include <sgf/utils/resource_id.h>

namespace sgf_core {
    struct ShaderTag {
        static const std::string TypeName;
    };
    using ShaderId = ResourceId<ShaderTag>;
}
