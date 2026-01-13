#pragma once

#include <memory>
#include "./input/input.h"

namespace sgf_core {
    class PlatformContext;

    class PlatformRuntime {
    public:
        ~PlatformRuntime();

        sgf_core::Input & Input();

        void onFrameBegin();
        void onFrameEnd();

    private:
        friend PlatformContext;

        const PlatformContext & context;
        sgf_core::Input input;

        std::unique_ptr<KeyboardInputInjector> keyboardInjector;
        std::unique_ptr<MouseInputInjector> mouseInjector;

        PlatformRuntime(const PlatformContext & context);

        void pollEvents();
    };
}
