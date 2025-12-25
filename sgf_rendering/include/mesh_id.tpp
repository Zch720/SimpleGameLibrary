#include "./mesh_id.h"

template <>
struct TypeName<MeshTag> {
    std::string operator()() const noexcept {
        return "Mesh";
    }
};
