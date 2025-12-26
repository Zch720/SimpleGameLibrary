#include "../../../../include/sgf/utils/exceptions/invalid_state.h"

namespace sgf_core {
    InvalidState::InvalidState(const std::string & message) : message(message) {
    }

    const char* InvalidState::what() const noexcept {
        return message.c_str();
    }
}
