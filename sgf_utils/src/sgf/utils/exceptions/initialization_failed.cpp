#include "../../../../include/sgf/utils/exceptions/initialization_failed.h"

namespace sgf_core {
    InitializationFailed::InitializationFailed(const std::string & message) : message(message) {
    }

    const char* InitializationFailed::what() const noexcept {
        return message.c_str();
    }
}
