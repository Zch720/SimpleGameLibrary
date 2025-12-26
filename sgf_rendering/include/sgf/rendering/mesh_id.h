#pragma once

#include <sgf/utils/resource_id.h>

namespace sgf_core {
    struct MeshTag {
        static const std::string TypeName;
    };
    using MeshId = ResourceId<MeshTag>;
}
