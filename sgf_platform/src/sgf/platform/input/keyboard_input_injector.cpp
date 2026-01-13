#include "../../../../internal_include/sgf/platform/input/keyboard_input_injector.h"

namespace sgf_core {
    KeyboardInputInjector::KeyboardInputInjector(Keyboard & keyboard): keyboard(keyboard) {
    }

    void KeyboardInputInjector::beginFrame() {
        keyboard.beginFrame();
    }

    void KeyboardInputInjector::onKeyPressed(Key key) {
        keyboard.onKeyPressed(key);
    }

    void KeyboardInputInjector::onKeyReleased(Key key) {
        keyboard.onKeyReleased(key);
    }
}
