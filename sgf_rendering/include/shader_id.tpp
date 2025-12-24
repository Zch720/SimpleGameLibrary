#pragma once

#include "./shader_id.h"

namespace std {
    template<>
    struct hash<ShaderId> {
        size_t operator()(const ShaderId & id) const {
            return ((size_t)id.getGen()) << 32 | id.getId();
        }
    };
}
