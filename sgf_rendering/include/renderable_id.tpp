#pragma once

#include "./renderable_id.h"

namespace std {
    template<>
    struct hash<RenderableId> {
        size_t operator()(const RenderableId & id) const {
            return ((size_t)id.getGen()) << 32 | id.getId();
        }
    };
}
