#include <gtest/gtest.h>
#include "../util.hpp"
#include "../../include/sgf/platform/platform_context.h"
#include "sgf/utils/exceptions/invalid_state.h"

using namespace sgf_core;

TEST(PlatformContextSuite, UsingCorrectStep) {
    ASSERT_NO_THROW({
        PlatformContext context;
        context.createWindow({ .width = 800, .height = 600, .title = "Test Window" });
        context.Window().setClearColor(0, 0, 0, 0);
        context.terminate();
    });
}

TEST(PlatformContextSuite, CreateSecondWindowShouldFailed) {
    PlatformContext context;
    context.createWindow({ .width = 800, .height = 600, .title = "Test Window" });
    ASSERT_THROW_MESSAGE(
        context.createWindow({ .width = 800, .height = 600, .title = "Test Window" }),
        InvalidState,
        "Already created a default window. Multiple windows are not supported yet."
    );
}

TEST(PlatformContextSuite, TerminateBeforeInitializeShouldFailed) {
    PlatformContext context;
    ASSERT_THROW_MESSAGE(
        context.terminate(),
        InvalidState,
        "PlatformContext has not initialize yet, or you already terminated. Please create a window to initial PlatformContext."
    );
}

TEST(PlatformContextSuite, TerminateTwiceShouldFailed) {
    PlatformContext context;
    context.createWindow({ .width = 800, .height = 600, .title = "Test Window" });
    context.terminate();
    ASSERT_THROW_MESSAGE(
        context.terminate(),
        InvalidState,
        "PlatformContext has not initialize yet, or you already terminated. Please create a window to initial PlatformContext."
    );
}

TEST(PlatformContextSuite, GetWindowBeforeCreateShouldFailed) {
    PlatformContext context;
    ASSERT_THROW_MESSAGE(
        context.Window(),
        InvalidState,
        "The default window has not been created yet. Please use PlatformContext::createWindow to create the default window."
    );
}
