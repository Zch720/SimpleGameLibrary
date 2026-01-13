#pragma once

#include <unordered_set>
#include "./key.h"

namespace sgf_core {
    class MouseInputInjector;

    class Mouse {
    public:
        struct Position {
            double x;
            double y;
        };
        struct Offset {
            double x;
            double y;
        };

        Position Pos() const;
        Offset ScrollOffset() const;

        bool isMouseButtonUp(MouseKey key) const;
        bool isMouseButtonDown(MouseKey key) const;
        bool isMouseButtonHold(MouseKey key) const;
    
    private:
        friend MouseInputInjector;

        std::unordered_set<MouseKey> pressedMouseKey;
        std::unordered_set<MouseKey> releasedMouseKey;
        std::unordered_set<MouseKey> holdMouseKey;

        Position position;
        Offset scrollOffset;

        void beginFrame();
        void onMouseButtonPressed(MouseKey key);
        void onMouseButtonReleased(MouseKey key);
        void onCursorMoved(Position pos);
        void onScrollScrolled(Offset offset);
    };
}
