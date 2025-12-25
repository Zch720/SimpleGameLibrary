#pragma once

#include <resource_id.h>

struct MaterialTag {
    static const std::string TypeName;
};
using MaterialId = ResourceId<MaterialTag>;
