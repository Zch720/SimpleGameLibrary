#pragma once

#include <sgf/utils/manager.h>
#include "./window.h"

namespace sgf_core {
    class PlatformContext;

    class WindowManager: public Manager<Window> {
    private:
        using Manager<Window>::create;

        friend PlatformContext;

        WindowManager();
    };
}
