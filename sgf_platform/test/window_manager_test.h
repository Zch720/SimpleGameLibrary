#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "./test_env.h"
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
};

TEST_F(WindowManagerSuite, CreateOneWindow) {
    ASSERT_NO_THROW(WindowManager::Instance().createWindow(800, 600, "Test Window"));
}

TEST_F(WindowManagerSuite, CreateTwoWindow) {
    WindowManager::Instance().createWindow(800, 600, "Test Window");
    ASSERT_NO_THROW(WindowManager::Instance().createWindow(800, 600, "Second Window"));
}

TEST_F(WindowManagerSuite, CheckWindowExist) {
    WindowId id = WindowManager::Instance().createWindow(800, 600, "Test Window");
    ASSERT_TRUE(WindowManager::Instance().isWindowExist(id));
    ASSERT_FALSE(WindowManager::Instance().isWindowExist(WindowId()));
}

TEST_F(WindowManagerSuite, CloseWindow) {
    WindowId id = WindowManager::Instance().createWindow(800, 600, "Test Window");
    
    ASSERT_FALSE(WindowManager::Instance().isWindowClose(id));
    WindowManager::Instance().closeWindow(id);
    ASSERT_TRUE(WindowManager::Instance().isWindowClose(id));
}

TEST_F(WindowManagerSuite, CannotOperateAnUnexistWindow) {
    ASSERT_THROW_MESSAGE(
        WindowManager::Instance().isWindowClose(WindowId()),
        std::runtime_error,
        "Cannot find window with id: 0, gen: 0"
    );
}

TEST_F(WindowManagerSuite, DestroyWindow) {
    WindowId id = WindowManager::Instance().createWindow(800, 600, "Test Window");

    WindowManager::Instance().destroyWindow(id);

    ASSERT_FALSE(WindowManager::Instance().isWindowExist(id));
}

TEST_F(WindowManagerSuite, CreateNewWindowAfterDestroy) {
    WindowId oldId = WindowManager::Instance().createWindow(800, 600, "Test Window");

    WindowManager::Instance().destroyWindow(oldId);
    WindowId newId = WindowManager::Instance().createWindow(800, 600, "Test Window");

    ASSERT_EQ(oldId.getId(), newId.getId());
    ASSERT_EQ(oldId.getGen(), 1);
    ASSERT_EQ(newId.getGen(), 2);
}

TEST_F(WindowManagerSuite, SetWindowAsCurrentContext) {
    WindowId idMain = WindowManager::Instance().createWindow(800, 600, "Test Window");
    WindowId idSecond = WindowManager::Instance().createWindow(400, 300, "Second Window");
    WindowManager::Instance().closeWindow(idSecond);

    WindowManager::Instance().useWindow(idMain);
    ASSERT_FALSE(glfwWindowShouldClose(glfwGetCurrentContext()));
    WindowManager::Instance().useWindow(idSecond);
    ASSERT_TRUE(glfwWindowShouldClose(glfwGetCurrentContext()));
}

TEST_F(WindowManagerSuite, RenameWindow) {
    if (skipHandTest) GTEST_SKIP();

    WindowId id = WindowManager::Instance().createWindow(800, 600, "Test Window");
    WindowManager::Instance().renameWindow(id, "New Title");

    PRINTF("There should be a window with title \"New Title\"\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    while (!WindowManager::Instance().isWindowClose(id)) {
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(id);
        }
        glfwPollEvents();
    }
}

TEST_F(WindowManagerSuite, ResizeWindow) {
    if (skipHandTest) GTEST_SKIP();

    WindowId id = WindowManager::Instance().createWindow(800, 600, "Test Window");
    WindowManager::Instance().resizeWindow(id, 400, 300);

    PRINTF("There should be a window with size 400x300\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    while (!WindowManager::Instance().isWindowClose(id)) {
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(id);
        }
        glfwPollEvents();
    }
}

TEST_F(WindowManagerSuite, SetWindowColor) {
    if (skipHandTest) GTEST_SKIP();

    WindowId id = WindowManager::Instance().createWindow(800, 600, "Test Window");
    WindowManager::Instance().setWindowColor(id, 1.0f, 0.0f, 0.0f, 1.0f);

    PRINTF("The window color should be red\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    while (!WindowManager::Instance().isWindowClose(id)) {
        WindowManager::Instance().clearWindow(id);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(id);
        }
        glfwPollEvents();
    }
}

TEST_F(WindowManagerSuite, CreateTwoWindowWithDifferentColor) {
    if (skipHandTest) GTEST_SKIP();

    WindowId idMain = WindowManager::Instance().createWindow(800, 600, "Test Window");
    WindowId idSecond = WindowManager::Instance().createWindow(400, 300, "Second Window");
    WindowManager::Instance().setWindowColor(idMain, 1.0f, 0.0f, 0.0f, 1.0f);
    WindowManager::Instance().setWindowColor(idSecond, 0.0f, 1.0f, 0.0f, 1.0f);

    PRINTF("There should be two window\n");
    PRINTF("The large ont is red, and the small one is green\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    while (!WindowManager::Instance().isWindowClose(idMain)) {
        WindowManager::Instance().clearWindow(idMain);
        WindowManager::Instance().clearWindow(idSecond);
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(idMain);
        }
        glfwPollEvents();
    }
}

TEST_F(WindowManagerSuite, ClearWindowsAtSameTime) {
    if (skipHandTest) GTEST_SKIP();
    
    WindowId idMain = WindowManager::Instance().createWindow(800, 600, "Test Window");
    WindowId idSecond = WindowManager::Instance().createWindow(400, 300, "Second Window");
    WindowManager::Instance().setWindowColor(idMain, 1.0f, 0.0f, 0.0f, 1.0f);
    WindowManager::Instance().setWindowColor(idSecond, 0.0f, 1.0f, 0.0f, 1.0f);

    PRINTF("There should be two window\n");
    PRINTF("The large ont is red, and the small one is green\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    while (!WindowManager::Instance().isWindowClose(idMain)) {
        WindowManager::Instance().clearAll();
        if (SuccessCheckFromInputForLoop("Window display wrong")) {
            WindowManager::Instance().closeWindow(idMain);
        }
        glfwPollEvents();
    }
}