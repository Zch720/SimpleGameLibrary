#pragma once

#include <sgf/utils/exceptions/initialization_failed.h>

namespace sgf_core {
    class GLControl {
    public:
        static void initGLFW();
        static void initGlad();
        static void terminate();
    };
}
