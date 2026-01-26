#include "../../../include/sgf/rendering/uniform_id.h"

namespace sgf_core {
    UniformId::UniformId(): materialId(), id(0) {
    }

    UniformId::UniformId(const MaterialId & materialId, uint32_t id): materialId(materialId), id(id) {
    }

    bool UniformId::isDefault() const {
        return materialId.getId() == 0 && id == 0;
    }

    MaterialId UniformId::getMaterialId() const {
        return materialId;
    }

    uint32_t UniformId::getId() const {
        return id;
    }

    std::string UniformId::toString() const {
        return "UniformId(materialId=" + materialId.toString() + ", id=" + std::to_string(id) + ")";
    }

    bool UniformId::operator==(const UniformId & other) const noexcept {
        return materialId == other.materialId && id == other.id;
    }

    bool UniformId::operator!=(const UniformId & other) const noexcept {
        return materialId != other.materialId || id != other.id;
    }
}

namespace std {
    size_t hash<sgf_core::UniformId>::operator()(const sgf_core::UniformId & id) const noexcept {
        return id.getId();
    }

    bool equal_to<sgf_core::UniformId>::operator()(const sgf_core::UniformId & left, const sgf_core::UniformId & right) const noexcept {
        return left.getMaterialId() == right.getMaterialId() && left.getId() == right.getId();
    }
}