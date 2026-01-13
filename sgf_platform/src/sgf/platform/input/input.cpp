#include "../../../../include/sgf/platform/input/input.h"

namespace sgf_core {
    sgf_core::Keyboard & Input::Keyboard() {
        return keyboard;
    }

    sgf_core::Mouse & Input::Mouse() {
        return mouse;
    }
}
