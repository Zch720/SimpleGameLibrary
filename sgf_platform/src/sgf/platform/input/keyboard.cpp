#include "../../../../include/sgf/platform/input/keyboard.h"

namespace sgf_core {
    bool Keyboard::isKeyUp(Key key) const {
        return releasedKey.find(key) != releasedKey.end();
    }
    
    bool Keyboard::isKeyDown(Key key) const {
        return pressedKey.find(key) != pressedKey.end();
    }
    
    bool Keyboard::isKeyHold(Key key) const {
        return holdKey.find(key) != holdKey.end();
    }

    void Keyboard::beginFrame() {
        pressedKey.clear();
        releasedKey.clear();
    }

    void Keyboard::onKeyPressed(Key key) {
        pressedKey.insert(key);
        holdKey.insert(key);
        if (releasedKey.find(key) != releasedKey.end()) {
            releasedKey.erase(key);
        }
    }

    void Keyboard::onKeyReleased(Key key) {
        releasedKey.insert(key);
        if (holdKey.find(key) != holdKey.end()) {
            holdKey.erase(key);
        }
        if (pressedKey.find(key) != pressedKey.end()) {
            pressedKey.erase(key);
        }
    }
}
