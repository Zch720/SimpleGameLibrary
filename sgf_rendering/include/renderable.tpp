#include "./renderable.h"

template <>
struct TypeName<Renderable> {
    std::string operator()() const noexcept {
        return "Renderable";
    }
};
