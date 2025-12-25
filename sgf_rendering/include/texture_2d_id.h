#pragma once

#include <resource_id.h>

struct Texture2DTag {
    static const std::string TypeName;
};
using Texture2DId = ResourceId<Texture2DTag>;
