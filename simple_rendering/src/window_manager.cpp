#include <stdexcept>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../include/window.h"
#include "../include/window_manager.h"

WindowManager WindowManager::instance;

WindowManager & WindowManager::Instance() {
    return instance;
}

WindowManager::WindowManager() {
    isFirstWindow = true;
    isRunning = false;
    windows = {};
}

WindowManager::~WindowManager() {
    terminate();
}

bool WindowManager::isWindowExist(std::string identifyName) {
    return windows.find(identifyName) != windows.end();
}

bool WindowManager::isWindowClose(std::string identifyName) {
    checkWindowExist(identifyName);
    return windows[identifyName]->isClose();
}

void WindowManager::createWindow(std::string identifyName, int width, int height, std::string title) {
    if (isWindowExist(identifyName)) {
        throw std::runtime_error("Cannot create window with same identify name");
    }

    if (isFirstWindow) initGlfw();

    windows[identifyName] = new Window(width, height, title);

    if (isFirstWindow) {
        windows[identifyName]->makeContextCurrent();
        initGlad();
        glEnable(GL_DEPTH_TEST);
        isFirstWindow = false;
        isRunning = true;
    }
}

void WindowManager::useWindow(std::string identifyName) {
    checkWindowExist(identifyName);
    windows[identifyName]->makeContextCurrent();
}

void WindowManager::clearAll() {
    for (auto & window : windows) {
        window.second->clear();
    }
}

void WindowManager::terminate() {
    if (!isRunning) return;
    for (auto & window : windows) {
        window.second->destroy();
        delete window.second;
    }
    windows.clear();
    glfwTerminate();
    isFirstWindow = true;
    isRunning = false;
}

void WindowManager::clearWindow(std::string identifyName) {
    checkWindowExist(identifyName);
    windows[identifyName]->clear();
}

void WindowManager::closeWindow(std::string identifyName) {
    checkWindowExist(identifyName);
    windows[identifyName]->close();
}

void WindowManager::renameWindow(std::string identifyName, std::string newTitle) {
    checkWindowExist(identifyName);
    windows[identifyName]->rename(newTitle);
}

void WindowManager::resizeWindow(std::string identifyName, int width, int height) {
    checkWindowExist(identifyName);
    windows[identifyName]->resize(width, height);
}

void WindowManager::setWindowColor(std::string identifyName, float r, float g, float b, float a) {
    checkWindowExist(identifyName);
    windows[identifyName]->setClearColor(r, g, b, a);
}

void WindowManager::initGlfw() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    initGlfwWindowHint();
}

void WindowManager::initGlfwWindowHint() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

void WindowManager::initGlad() {
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void WindowManager::checkWindowExist(std::string identifyName) {
    if (!isWindowExist(identifyName)) {
        throw std::runtime_error("Cannot find window with identify name: " + identifyName);
    }
}