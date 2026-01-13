#include "../../../../internal_include/sgf/platform/input/mouse_input_injector.h"

namespace sgf_core {
    MouseInputInjector::MouseInputInjector(Mouse & mouse): mouse(mouse) {
    }

    void MouseInputInjector::beginFrame() {
        mouse.beginFrame();
    }

    void MouseInputInjector::onMouseButtonPressed(MouseKey key) {
        mouse.onMouseButtonPressed(key);
    }

    void MouseInputInjector::onMouseButtonReleased(MouseKey key) {
        mouse.onMouseButtonReleased(key);
    }

    void MouseInputInjector::onCursorMoved(Mouse::Position pos) {
        mouse.onCursorMoved(pos);
    }

    void MouseInputInjector::onScrollScrolled(Mouse::Offset offset) {
        mouse.onScrollScrolled(offset);
    }
}
