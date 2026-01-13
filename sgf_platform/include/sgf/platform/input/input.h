#pragma once

#include "./keyboard.h"
#include "./mouse.h"

namespace sgf_core {
    class Input {
    public:
        sgf_core::Keyboard & Keyboard();
        sgf_core::Mouse & Mouse();

    private:
        sgf_core::Keyboard keyboard;
        sgf_core::Mouse mouse;
    };
}
