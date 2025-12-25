#pragma once

#include <resource_id.h>

struct RenderableTag {
    static const std::string TypeName;
};
using RenderableId = ResourceId<RenderableTag>;
