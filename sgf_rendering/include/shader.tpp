#include "./shader.h"

template <>
struct TypeName<Shader> {
    std::string operator()() const noexcept {
        return "Shader";
    }
};
