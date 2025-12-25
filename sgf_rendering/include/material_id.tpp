#include "material_id.h"

template <>
struct TypeName<MaterialTag> {
    std::string operator()() const noexcept {
        return "Material";
    }
};
