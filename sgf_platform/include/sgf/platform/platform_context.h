#pragma once

#include <sgf/utils/manager.h>
#include <sgf/utils/exceptions/invalid_state.h>
#include "./platform_runtime.h"
#include "./window/window_manager.h"

namespace sgf_core {
    class PlatformContext {
    public:
        PlatformContext();

        void createWindow(const Window::Construct & windowConstruct);
        void terminate();

        sgf_core::PlatformRuntime & Runtime();
        sgf_core::Window & Window() const;

        uint32_t getWindowClearBuffer() const;
        void setWindowClearBuffer(uint32_t buffer);
    
    private:
        bool isInitialized;

        WindowManager windowManager;
        WindowId defaultWindowId;

        PlatformRuntime runtime;

        uint32_t windowClearBuffer;
    };
}
