#pragma once


#include "../../../../include/sgf/platform/input/mouse.h"
#include "../../../../include/sgf/platform/input/key.h"

namespace sgf_core {
    class MouseInputInjector {
    public:
        MouseInputInjector(Mouse & input);

        void beginFrame();
        void onMouseButtonPressed(MouseKey key);
        void onMouseButtonReleased(MouseKey key);
        void onCursorMoved(Mouse::Position pos);
        void onScrollScrolled(Mouse::Offset offset);

    private:
        Mouse & mouse;
    };
}