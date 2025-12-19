#pragma once

#include "./window.h"
#include "./window_manager.h"
#include "./renderable/renderable_id.h"

template<typename R, typename... Args>
RenderableId WindowManager::createRenderable(WindowId id, Args&&... args) {
    checkWindowExist(id);
    return windows[id.getId() - 1]->createRenderable<R>(std::forward<Args>(args)...);
}

template<typename R>
R& WindowManager::getRenderable(WindowId id, RenderableId renderableId) {
    checkWindowExist(id);
    return windows[id.getId() - 1]->getRenderable<R>(renderableId);
}
