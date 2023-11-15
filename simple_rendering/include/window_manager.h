#pragma once

#include <string>
#include <unordered_map>

class Window;

class WindowManager {
public:
    static WindowManager & Instance();

    WindowManager();
    ~WindowManager();

    bool isWindowExist(std::string identifyName);
    bool isWindowClose(std::string identifyName);

    void createWindow(std::string identifyName, int width, int height, std::string title);
    void useWindow(std::string identifyName);
    void clearAll();
    void terminate();

    void clearWindow(std::string identifyName);
    void closeWindow(std::string identifyName);
    void renameWindow(std::string identifyName, std::string newTitle);
    void resizeWindow(std::string identifyName, int width, int height);
    void setWindowColor(std::string identifyName, float r, float g, float b, float a);

private:
    static WindowManager instance;

    bool isFirstWindow;
    std::unordered_map<std::string, Window *> windows;

    void initGlfw();
    void initGlfwWindowHint();
    void initGlad();

    void checkWindowExist(std::string identifyName);
};