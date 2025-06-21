#pragma once

#include "./window.h"
#include "./window_manager.h"

template<typename R, typename... Args>
void WindowManager::createRenderable(std::string identifyName, std::string renderableIdentifyName, Args&&... args) {
    checkWindowExist(identifyName);
    windows[identifyName]->createRenderable<R>(renderableIdentifyName, std::forward<Args>(args)...);
}

template<typename R>
R& WindowManager::getRenderable(std::string identifyName, std::string renderableIdentifyName) {
    checkWindowExist(identifyName);
    return windows[identifyName]->getRenderable<R>(renderableIdentifyName);
}
