#pragma once

#include "./window.h"
#include "./window_manager.h"

template<typename R, typename... Args>
void WindowManager::createRenderable(WindowId id, std::string renderableIdentifyName, Args&&... args) {
    checkWindowExist(id);
    windows[id.getId() - 1]->createRenderable<R>(renderableIdentifyName, std::forward<Args>(args)...);
}

template<typename R>
R& WindowManager::getRenderable(WindowId id, std::string renderableIdentifyName) {
    checkWindowExist(id);
    return windows[id.getId() - 1]->getRenderable<R>(renderableIdentifyName);
}
