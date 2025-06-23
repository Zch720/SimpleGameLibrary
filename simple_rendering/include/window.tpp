#pragma once

#include <stdexcept>
#include "./window.h"

template<typename R, typename... Args>
void Window::createRenderable(std::string renderableIdentifyName, Args&&... args) {
    static_assert(std::is_base_of<Renderable, R>::value, "R must be subclass of Renderable");
    R* r = new R(std::forward<Args>(args)...);
    renderables[renderableIdentifyName] = r;
}

template<typename R>
R& Window::getRenderable(std::string renderableIdentifyName) {
    if (!isRenderableExist(renderableIdentifyName)) {
        throw new std::runtime_error("Cannot find renderable with name: " + renderableIdentifyName);
    }

    Renderable * r = renderables[renderableIdentifyName];
    R * castedR = dynamic_cast<R *>(r);
    if (castedR == nullptr) {
        throw new std::runtime_error("Casting renderable with name: " + renderableIdentifyName + " to type: " + typeid(R).name() + " Failed");
    }
    return *castedR;
}