#pragma once

#include <sgf/utils/resource_id.h>

namespace sgf_core {
    struct AudioSourceTag {
        static const std::string TypeName;
    };
    using AudioSourceId = ResourceId<AudioSourceTag>;
}
