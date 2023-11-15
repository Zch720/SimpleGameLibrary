#include <gtest/gtest.h>
#include "./util.hpp"
#include "../include/window.h"

class WindowSuite : public ::testing::Test {
protected:
    void SetUp() override {
        if (skipAll) {
            GTEST_SKIP();
        }

        SetUpGlfw();
    }

    void TearDown() override {
        if (skipAll) {
            return;
        }

        glfwTerminate();
    }

    void SetUpGlfw() {
        if (!glfwInit()) {
            skipAll = true;
            FAIL() << "Failed to initialize GLFW";
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    }

    void SetUpGlad() {
        if (!gladLoadGL(glfwGetProcAddress)) {
            skipAll = true;
            FAIL() << "Failed to initialize GLAD";
        }
    }

    Window CreateDefaultWindow(int width, int height, const char * title) {
        Window defaultWindow(width, height, title);
        defaultWindow.makeContextCurrent();

        SetUpGlad();

        return defaultWindow;
    }

    Window CreateWindow(int width, int height, const char * title) {
        Window window(width, height, title);

        return window;
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

    static bool skipAll;
    static bool skipHandTest;
};

bool WindowSuite::skipAll = false;
bool WindowSuite::skipHandTest = true;

TEST_F(WindowSuite, CreateWindow) {
    Window window(800, 600, "Test Window");
    window.makeContextCurrent();

    SetUpGlad();

    ASSERT_EQ(window.getGLFWWindow(), glfwGetCurrentContext());

    glfwSetWindowShouldClose(window.getGLFWWindow(), true);
}

TEST_F(WindowSuite, CloseWindow) {
    Window window = CreateDefaultWindow(800, 600, "Test Window");
    
    ASSERT_FALSE(glfwWindowShouldClose(window.getGLFWWindow()));
    window.close();

    ASSERT_TRUE(glfwWindowShouldClose(window.getGLFWWindow()));
}

TEST_F(WindowSuite, DestroyWindow) {
    Window window = CreateDefaultWindow(800, 600, "Test Window");

    window.destroy();

    ASSERT_EQ(window.getGLFWWindow(), nullptr);
}

TEST_F(WindowSuite, CheckWindowDisplay) {
    if (skipHandTest) GTEST_SKIP();

    CreateDefaultWindow(800, 600, "Test Window");

    PRINTF("Should display window with size 800x600\n");
    PRINTF("And title \"Test Window\"\n")
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    char c = 0;
    while (c != 's' && c != 'f') {
        if (_kbhit()) c = getchar();
    }

    EndOfGetKey();
    CheckSuccess(c == 's', "Window display wrong");
}

TEST_F(WindowSuite, RenameWindow) {
    if (skipHandTest) GTEST_SKIP();

    Window window = CreateDefaultWindow(800, 600, "Test Window");

    window.rename("New Title");
    
    PRINTF("The title should be \"New Title\"\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    char c = 0;
    while (c != 's' && c != 'f') {
        if (_kbhit()) c = getchar();
    }

    EndOfGetKey();
    CheckSuccess(c == 's', "Window display wrong");
}

TEST_F(WindowSuite, ResizeWindow) {
    if (skipHandTest) GTEST_SKIP();

    Window window = CreateDefaultWindow(800, 600, "Test Window");

    window.resize(200, 200);
    
    PRINTF("The window size should be 200x200\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    char c = 0;
    while (c != 's' && c != 'f') {
        if (_kbhit()) c = getchar();
    }

    EndOfGetKey();
    CheckSuccess(c == 's', "Window display wrong");
}

TEST_F(WindowSuite, SetClearColor) {
    if (skipHandTest) GTEST_SKIP();

    Window window = CreateDefaultWindow(800, 600, "Test Window");
    window.setClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    window.clear();

    PRINTF("The window color should be red\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    char c = 0;
    while (c != 's' && c != 'f') {
        if (_kbhit()) c = getchar();
    }

    EndOfGetKey();
    CheckSuccess(c == 's', "Window display wrong");
}

TEST_F(WindowSuite, CreateTwoWindow) {
    if (skipHandTest) GTEST_SKIP();

    CreateDefaultWindow(800, 600, "Test Window");
    CreateWindow(400, 300, "Second Window");

    PRINTF("There should be two windows\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    char c = 0;
    while (c != 's' && c != 'f') {
        if (_kbhit()) c = getchar();
    }

    EndOfGetKey();
    CheckSuccess(c == 's', "Windows display wrong");
}

TEST_F(WindowSuite, TwoWindowWithDifferentColor) {
    if (skipHandTest) GTEST_SKIP();

    Window defaultWindow = CreateDefaultWindow(800, 600, "Test Window");
    Window window = CreateWindow(400, 300, "Second Window");
    defaultWindow.setClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    window.setClearColor(0.0f, 1.0f, 0.0f, 1.0f);

    defaultWindow.clear();
    window.clear();

    PRINTF("There should be two windows\n");
    PRINTF("The big one is red, and the small one is green\n");
    PRINTF("If success press 's', otherwise press 'f' ");
    fflush(stdout);

    char c = 0;
    while (c != 's' && c != 'f') {
        if (_kbhit()) c = getchar();
    }

    EndOfGetKey();
    CheckSuccess(c == 's', "Windows display wrong");
}