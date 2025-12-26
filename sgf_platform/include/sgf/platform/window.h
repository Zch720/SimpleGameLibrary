#pragma once

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
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

        GLFWwindow * getGLFWWindow();

        void setClearColor(float r, float g, float b, float a);

        bool isClose();

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

        GLFWwindow * window;
        ClearColor clearColor;
    };
}
