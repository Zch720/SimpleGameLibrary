#pragma once

#include <memory>
#include <string>
#include <sgf/utils/resource.h>
#include "./window_id.h"
#include "../input/key.h"

namespace sgf_core {
    class PlatformContext;
    class KeyboardInputInjector;
    class MouseInputInjector;
    
    class Window: public Resource<Window, WindowId> {
    public:
        static const std::string TypeName;
        struct Construct {
            int width;
            int height;
            const std::string & title;
        };

        Window(const Id & id, const Construct & constructParameter);
        ~Window();

        void setClearColor(float r, float g, float b, float a);

        bool isClose() const;

        void makeContextCurrent();

        void swapBuffer();
        void clearBuffer(uint32_t bits);
        void close();

        void rename(std::string title);
        void resize(int width, int height);

    private:
        friend PlatformContext;

        struct ClearColor {
            float r = 0;
            float g = 0;
            float b = 0;
            float a = 1;
        };
        struct WindowImpl;

        std::unique_ptr<WindowImpl> impl;
        ClearColor clearColor;

        void setKeyboardInputInjector(KeyboardInputInjector & keyboardInjector);
        void setMouseInputInjector(MouseInputInjector & mouseInjector);

        void keyPressedHandler(Key key);
        void keyReleasedHandler(Key key);
        void mousePressedHandler(MouseKey key);
        void mouseReleasedHandler(MouseKey key);
        void cursorMovedHandler(double x, double y);
        void scrollScrolledHandler(double x, double y);
    };
}
