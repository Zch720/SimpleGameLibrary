#include "../../../include/sgf/platform/gl_control.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace sgf_core {
    void GLControl::initGLFW() {
        if (!glfwInit()) {
            throw InitializationFailed("Failed to initialize GLFW");
        }
    }

    void GLControl::initGlad() {
        if (!gladLoadGL(glfwGetProcAddress)) {
            throw InitializationFailed("Failed to load GL functions by Glad");
        }
    }

    void GLControl::terminate() {
        glfwTerminate();
    }
}
