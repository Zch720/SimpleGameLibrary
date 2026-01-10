#pragma once

#include <memory>
#include <string>
#include <sgf/utils/resource.h>
#include "./window_id.h"

namespace sgf_core {
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
        struct ClearColor {
            float r = 0;
            float g = 0;
            float b = 0;
            float a = 1;
        };
        struct WindowImpl;

        std::unique_ptr<WindowImpl> impl;
        ClearColor clearColor;
    };
}
