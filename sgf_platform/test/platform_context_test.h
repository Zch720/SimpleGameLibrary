#include <gtest/gtest.h>
#include "./util.hpp"
#include "../include/sgf/platform/platform_context.h"

using namespace sgf_core;

TEST(PlatformContextSuite, UsingCorrectStep) {
    ASSERT_NO_THROW({
        PlatformContext context;
        WindowId id = context.createDefaultWindow({ .width = 800, .height = 600, .title = "Test Window" });
        context.WindowManager().getRef(id).setClearColor(0, 0, 0, 0);
        context.terminate();
    });
}

TEST(PlatformContextSuite, TryGetWindowManagerBrforeCreateDefaultWindowShouldFailed) {
    PlatformContext context;
    ASSERT_THROW_MESSAGE(
        context.WindowManager(),
        InvalidState,
        "Should use WindowManager after create the default window."
    );
}

TEST(PlatformContextSuite, InitialzeTwiceShouldFailed) {
    PlatformContext context;
    context.createDefaultWindow({ .width = 800, .height = 600, .title = "Test Window" });
    ASSERT_THROW_MESSAGE(
        context.createDefaultWindow({ .width = 800, .height = 600, .title = "Test Window" }),
        InvalidState,
        "Default window already created."
    );
    context.terminate();
}

TEST(PlatformContextSuite, TerminateBeforeInitializeShouldFailed) {
    PlatformContext context;
    ASSERT_THROW_MESSAGE(
        context.terminate(),
        InvalidState,
        "PlatformContext has not initialize yet, or you already treminated."
    );
}

TEST(PlatformContextSuite, TerminateTwiceShouldFailed) {
    PlatformContext context;
    context.createDefaultWindow({ .width = 800, .height = 600, .title = "Test Window" });
    context.terminate();
    ASSERT_THROW_MESSAGE(
        context.terminate(),
        InvalidState,
        "PlatformContext has not initialize yet, or you already treminated."
    );
}
