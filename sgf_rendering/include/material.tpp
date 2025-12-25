#include "./material.h"

template <>
struct TypeName<Material> {
    std::string operator()() const noexcept {
        return "Material";
    }
};
