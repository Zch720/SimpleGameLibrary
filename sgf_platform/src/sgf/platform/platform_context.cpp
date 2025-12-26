#include "../../../include/sgf/platform/platform_context.h"
#include "../../../include/sgf/platform/gl_control.h"

namespace sgf_core {
    PlatformContext::PlatformContext(): isInitialized(false) {
    }

    Manager<Window> & PlatformContext::WindowManager() {
        if (!isInitialized) {
            throw InvalidState("Should use WindowManager after create the default window.");
        }
        return windowManager;
    }

    WindowId PlatformContext::createDefaultWindow(const Window::Construct & windowConstruct) {
        if (isInitialized) {
            throw InvalidState("Default window already created.");
        }
        GLControl::initGLFW();
        WindowId windowId = windowManager.create(windowConstruct);
        windowManager.getRef(windowId).makeContextCurrent();
        GLControl::initGlad();
        isInitialized = true;
        return windowId;
    }

    void PlatformContext::terminate() {
        if (!isInitialized) {
            throw InvalidState("PlatformContext has not initialize yet, or you already treminated.");
        }
        windowManager.destroyAll();
        GLControl::terminate();
        isInitialized = false;
    }
}
