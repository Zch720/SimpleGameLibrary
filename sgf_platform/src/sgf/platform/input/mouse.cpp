#include "../../../../include/sgf/platform/input/mouse.h"

namespace sgf_core {
    Mouse::Position Mouse::Pos() const {
        return position;
    }

    Mouse::Offset Mouse::ScrollOffset() const {
        return scrollOffset;
    }

    bool Mouse::isMouseButtonUp(MouseKey key) const {
        return releasedMouseKey.find(key) != releasedMouseKey.end();
    }

    bool Mouse::isMouseButtonDown(MouseKey key) const {
        return pressedMouseKey.find(key) != pressedMouseKey.end();
    }

    bool Mouse::isMouseButtonHold(MouseKey key) const {
        return holdMouseKey.find(key) != holdMouseKey.end();
    }

    void Mouse::beginFrame() {
        pressedMouseKey.clear();
        releasedMouseKey.clear();
        scrollOffset = {0, 0};
    }

    void Mouse::onMouseButtonPressed(MouseKey key) {
        pressedMouseKey.insert(key);
        holdMouseKey.insert(key);
        if (releasedMouseKey.find(key) != releasedMouseKey.end()) {
            releasedMouseKey.erase(key);
        }
    }

    void Mouse::onMouseButtonReleased(MouseKey key) {
        releasedMouseKey.insert(key);
        if (holdMouseKey.find(key) != holdMouseKey.end()) {
            holdMouseKey.erase(key);
        }
        if (pressedMouseKey.find(key) != pressedMouseKey.end()) {
            pressedMouseKey.erase(key);
        }
    }

    void Mouse::onCursorMoved(Position pos) {
        position = pos;
    }

    void Mouse::onScrollScrolled(Offset offset) {
        scrollOffset = offset;
    }
}
