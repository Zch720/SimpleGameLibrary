#include "texture_2d_id.h"

template <>
struct TypeName<Texture2DTag> {
    std::string operator()() const noexcept {
        return "Texture2D";
    }
};
