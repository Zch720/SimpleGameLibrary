#pragma once

#include <stdexcept>
#include "./window.h"

template<typename R, typename... Args>
RenderableId Window::createRenderable(Args&&... args) {
    static_assert(std::is_base_of<Renderable, R>::value, "R must be subclass of Renderable");
    R* r = new R(std::forward<Args>(args)...);
    RenderableId renderableId = newRenderableId();
    renderables[renderableId.getId() - 1] = r;
    return renderableId;
}

template<typename R>
R& Window::getRenderable(RenderableId renderableId) {
    if (!isRenderableExist(renderableId)) {
        throw new std::runtime_error("Cannot find renderable with id: " + std::to_string(renderableId.getId()));
    }

    Renderable * r = renderables[renderableId.getId() - 1];
    R * castedR = dynamic_cast<R *>(r);
    if (castedR == nullptr) {
        throw new std::runtime_error("Casting renderable with id: " + std::to_string(renderableId.getId()) + " to type: " + typeid(R).name() + " Failed");
    }
    return *castedR;
}