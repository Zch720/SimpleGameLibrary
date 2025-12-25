#include "./mesh.h"

template <>
struct TypeName<Mesh> {
    std::string operator()() const noexcept {
        return "Mesh";
    }
};
