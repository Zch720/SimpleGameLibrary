#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "./util.hpp"
#include "../include/window_manager.h"

class WindowManagerSuite : public ::testing::Test {
protected:
    void TearDown() override {
        WindowManager::Instance().terminate();
    }
    
    void EndOfGetKey() {
        fflush(stdin);
        printf("\n");
    }

    void CheckSuccess(bool success, std::string message) {
        if (success) {
            SUCCEED();
        } else {
            FAIL() << message;
        }
    }

    static bool skipHandTest;
};

bool WindowManagerSuite::skipHandTest = false;

TEST_F(WindowManagerSuite, CreateOneWindow) {
    ASSERT_NO_THROW(WindowManager::Instance().createWindow("main window", 800, 600, "Test Window"));
}

TEST_F(WindowManagerSuite, CreateTwoWindow) {
    WindowManager::Instance().createWindow("main window", 800, 600, "Test Window");
    ASSERT_NO_THROW(WindowManager::Instance().createWindow("second window", 800, 600, "Second Window"));
}

TEST_F(WindowManagerSuite, CreateTwoWindowWithSameIdentifyNameShouldFail) {
    WindowManager::Instance().createWindow("main window", 800, 600, "Test Window");
    ASSERT_THROW_MESSAGE(
        WindowManager::Instance().createWindow("main window", 400, 300, "Second Window"),
        std::runtime_error,
        "Cannot create window with same identify name"
    );
}

TEST_F(WindowManagerSuite, CheckWindowExist) {
    WindowManager::Instance().createWindow("main window", 800, 600, "Test Window");
    ASSERT_TRUE(WindowManager::Instance().isWindowExist("main window"));
    ASSERT_FALSE(WindowManager::Instance().isWindowExist("second window"));
}

TEST_F(WindowManagerSuite, CloseWindow) {
    WindowManager::Instance().createWindow("main window", 800, 600, "Test Window");
    
    ASSERT_FALSE(WindowManager::Instance().isWindowClose("main window"));
    WindowManager::Instance().closeWindow("main window");
    ASSERT_TRUE(WindowManager::Instance().isWindowClose("main window"));
}

TEST_F(WindowManagerSuite, CannotOperateAnUnexistWindow) {
    ASSERT_THROW_MESSAGE(
        WindowManager::Instance().isWindowClose("main window"),
        std::runtime_error,
        "Cannot find window with identify name: main window"
    );
}

TEST_F(WindowManagerSuite, SetWindowAsCurrentContext) {
    WindowManager::Instance().createWindow("main window", 800, 600, "Test Window");
    WindowManager::Instance().createWindow("second window", 400, 300, "Second Window");
    WindowManager::Instance().closeWindow("second window");

    WindowManager::Instance().useWindow("main window");
    ASSERT_FALSE(glfwWindowShouldClose(glfwGetCurrentContext()));
    WindowManager::Instance().useWindow("second window");
    ASSERT_TRUE(glfwWindowShouldClose(glfwGetCurrentContext()));
}

TEST_F(WindowManagerSuite, RenameWindow) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createWindow("main window", 800, 600, "Test Window");
    WindowManager::Instance().renameWindow("main window", "New Title");

    PRINTF("There should be a window with title \"New Title\"\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);
    SuccessCheckFromInput("Window display wrong");
}

TEST_F(WindowManagerSuite, SetWindowColor) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createWindow("main window", 800, 600, "Test Window");
    WindowManager::Instance().setWindowColor("main window", 1.0f, 0.0f, 0.0f, 1.0f);
    WindowManager::Instance().clearWindow("main window");

    PRINTF("The window color should be red\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);
    SuccessCheckFromInput("Window display wrong");
}

TEST_F(WindowManagerSuite, CreateTwoWindowWithDifferentColor) {
    if (skipHandTest) GTEST_SKIP();

    WindowManager::Instance().createWindow("main window", 800, 600, "Test Window");
    WindowManager::Instance().createWindow("second window", 400, 300, "Second Window");
    WindowManager::Instance().setWindowColor("main window", 1.0f, 0.0f, 0.0f, 1.0f);
    WindowManager::Instance().setWindowColor("second window", 0.0f, 1.0f, 0.0f, 1.0f);
    WindowManager::Instance().clearWindow("main window");
    WindowManager::Instance().clearWindow("second window");

    PRINTF("There should be two window\n");
    PRINTF("The large ont is red, and the small one is green\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);
    SuccessCheckFromInput("Window display wrong");
}

TEST_F(WindowManagerSuite, ClearWindowsAtSameTime) {
    if (skipHandTest) GTEST_SKIP();
    
    WindowManager::Instance().createWindow("main window", 800, 600, "Test Window");
    WindowManager::Instance().createWindow("second window", 400, 300, "Second Window");
    WindowManager::Instance().setWindowColor("main window", 1.0f, 0.0f, 0.0f, 1.0f);
    WindowManager::Instance().setWindowColor("second window", 0.0f, 1.0f, 0.0f, 1.0f);
    WindowManager::Instance().clearAll();

    PRINTF("There should be two window\n");
    PRINTF("The large ont is red, and the small one is green\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);
    SuccessCheckFromInput("Window display wrong");
}