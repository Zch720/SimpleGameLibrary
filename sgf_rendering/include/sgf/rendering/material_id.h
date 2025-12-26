#pragma once

#include <sgf/utils/resource_id.h>

namespace sgf_core {
    struct MaterialTag {
        static const std::string TypeName;
    };
    using MaterialId = ResourceId<MaterialTag>;
}
