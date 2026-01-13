#include "../../../include/sgf/platform/platform_runtime.h"

#include <GLFW/glfw3.h>
#include <memory>
#include "../../../include/sgf/platform/platform_context.h"
#include "../../../internal_include/sgf/platform/input/keyboard_input_injector.h"
#include "../../../internal_include/sgf/platform/input/mouse_input_injector.h"

namespace sgf_core {
    PlatformRuntime::PlatformRuntime(const PlatformContext & context): context(context), input() {
        keyboardInjector = std::make_unique<KeyboardInputInjector>(input.Keyboard());
        mouseInjector = std::make_unique<MouseInputInjector>(input.Mouse());
    }

    PlatformRuntime::~PlatformRuntime() = default;

    sgf_core::Input & PlatformRuntime::Input() {
        return input;
    }

    void PlatformRuntime::onFrameBegin() {
        context.Window().clearBuffer(context.getWindowClearBuffer());
        keyboardInjector->beginFrame();
        mouseInjector->beginFrame();
        pollEvents();
    }

    void PlatformRuntime::onFrameEnd() {
        context.Window().swapBuffer();
    }

    void PlatformRuntime::pollEvents() {
        glfwPollEvents();
    }
}
