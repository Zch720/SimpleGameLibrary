#pragma once

#include <sgf/utils/resource_id.h>

struct ShaderTag {
    static const std::string TypeName;
};
using ShaderId = ResourceId<ShaderTag>;
