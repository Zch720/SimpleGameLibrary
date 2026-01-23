#pragma once

#include <sgf/utils/resource_id.h>

namespace sgf_core {
    struct AudioDataTag {
        static const std::string TypeName;
    };
    using AudioDataId = ResourceId<AudioDataTag>;
};
