#pragma once

#include <unordered_set>
#include "./key.h"

namespace sgf_core {
    class KeyboardInputInjector;

    class Keyboard {
    public:
        bool isKeyUp(Key key) const;
        bool isKeyDown(Key key) const;
        bool isKeyHold(Key key) const;
    
    private:
        friend KeyboardInputInjector;

        std::unordered_set<Key> pressedKey;
        std::unordered_set<Key> releasedKey;
        std::unordered_set<Key> holdKey;
    
        void beginFrame();
        void onKeyPressed(Key key);
        void onKeyReleased(Key key);
    };
}
