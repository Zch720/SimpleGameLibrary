#pragma once

#include <sgf/utils/manager.h>
#include <sgf/utils/exceptions/invalid_state.h>
#include "./window.h"

namespace sgf_core {
    class PlatformContext {
    public:
        PlatformContext();

        Manager<Window> & WindowManager();

        WindowId createDefaultWindow(const Window::Construct & windowConstruct);
        void terminate();
    
    private:
        Manager<Window> windowManager;

        bool isInitialized;
    };
}
