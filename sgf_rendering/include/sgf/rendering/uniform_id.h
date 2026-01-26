#pragma once

#include <cstdint>
#include "./material_id.h"

namespace sgf_core {
    class Material;

    class UniformId {
    public:
        UniformId();

        bool isDefault() const;

        MaterialId getMaterialId() const;
        uint32_t getId() const;

        std::string toString() const;

        bool operator==(const UniformId & other) const noexcept;
        bool operator!=(const UniformId & other) const noexcept;

    private:
        friend Material;

        UniformId(const MaterialId & materialId, uint32_t id);

        MaterialId materialId;
        uint32_t id;
    };
}

namespace std {
    template <>
    struct hash<sgf_core::UniformId> {
        size_t operator()(const sgf_core::UniformId & id) const noexcept;
    };
    
    template <>
    struct equal_to<sgf_core::UniformId> {
        bool operator()(const sgf_core::UniformId & left, const sgf_core::UniformId & right) const noexcept;
    };
}
