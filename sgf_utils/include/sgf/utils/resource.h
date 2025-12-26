#pragma once

#include <string>
#include "./resource_id.h"

namespace sgf_core {
    template <typename T, typename TId>
    class Resource {
    public:
        using Id = TId;
        struct Construct;

        Id getId() const;

        static std::string getTypeName();

    protected:
        Id id;
    };
}

#include "./resource.tpp"
