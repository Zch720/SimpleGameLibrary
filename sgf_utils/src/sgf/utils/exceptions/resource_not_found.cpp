#include "../../../../include/sgf/utils/exceptions/resource_not_found.h"

namespace sgf {
    ResourceNotFound::ResourceNotFound(const std::string & message) : message(message) {
    }

    const char* ResourceNotFound::what() const noexcept {
        return message.c_str();
    }
}