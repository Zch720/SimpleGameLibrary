#pragma once

#include <sgf/utils/resource_id.h>

struct MeshTag {
    static const std::string TypeName;
};
using MeshId = ResourceId<MeshTag>;
