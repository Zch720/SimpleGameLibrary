#pragma once

#include "../../../../include/sgf/platform/input/key.h"
#include "../../../../include/sgf/platform/input/keyboard.h"

namespace sgf_core {
    class KeyboardInputInjector {
    public:
        KeyboardInputInjector(Keyboard & keyboard);

        void beginFrame();
        void onKeyPressed(Key key);
        void onKeyReleased(Key key);
    
    private:
        Keyboard & keyboard;
    };
}
