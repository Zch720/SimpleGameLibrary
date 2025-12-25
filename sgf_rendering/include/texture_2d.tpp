#include "./texture_2d.h"

template <>
struct TypeName<Texture2D> {
    std::string operator()() const noexcept {
        return "Texture2D";
    }
};
