#include "resource.h"

namespace sgf_core {
    template <typename T, typename TId>
    typename Resource<T, TId>::Id Resource<T, TId>::getId() const {
        return id;
    }

    template <typename T, typename TId>
    std::string Resource<T, TId>::getTypeName() {
        return T::TypeName;
    }
}
