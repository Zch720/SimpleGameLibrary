# Simple Game Library

This is a game library based on GLFW. Is is designed to be simple and easy to manage windows and rendering object.

## Features

- [x] Manage windows
- [x] Manage shaders
- [ ] Provide basic rendering objects: include line, triangle, rectangle, circle, image, text, etc.
- [ ] Manage audios
- [ ] Manage user input

## Usage

### Require

- C++ 14
- CMake 3.14 or later

#### Require Libraries

Ubuntu: `sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev`

#### OS

- Windows: support
- Linux: support
- MacOS: not tested

### CMake

This library is not finished yet. If you want to use the feature from sub-project `SimpleRendering` library of this project, you can link the library `simple_rendering` to your project.

```cmake
add_subdirectory(path_to_simple_game_library)

target_link_libraries(your_project PRIVATE simple_rendering)
```

## Example

### Simple Rendering

- Create a window and render a red triangle

```cpp
#include <window_manager.h>
#include <shader_manager.h>
#include <renderable/shapes/triangle.h>
#include <glad/gl.h> // This will be removed after adding a event manager
#include <GLFW/glfw3.h> // This will be removed after adding a event manager

#define MAIN_WINDOW_NAME    "main window"
#define MAIN_WINDOW_WIDTH   800
#define MAIN_WINDOW_HEIGHT  600
#define DEFAULT_SHADER_NAME "triangle shader"

#define VERTEX_SHADER   "#version 330 core\n"                       \
                        "layout (location = 0) in vec3 aPos;\n"     \
                        "uniform mat4 model = mat4(1.0);\n"         \
                        "void main() {\n"                           \
                        "   gl_Position = model * vec4(aPos, 1.0);\n"  \
                        "}"

#define FRAGMENT_SHADER "#version 330 core\n"               \
                        "uniform vec4 color = vec4(1.0);\n" \
                        "out vec4 FragColor;\n"             \
                        "void main() {\n"                   \
                        "   FragColor = color;\n"              \
                        "}"

int main() {
    WindowManager::Instance().createWindow(MAIN_WINDOW_NAME, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, "Test Window");
    ShaderManager::Instance().createShader(DEFAULT_SHADER_NAME, VERTEX_SHADER, FRAGMENT_SHADER);
    ShaderManager::Instance().registerShaderUniformVariable(DEFAULT_SHADER_NAME, "color", "color");
    ShaderManager::Instance().registerShaderUniformVariable(DEFAULT_SHADER_NAME, "transform", "model");
    
    Triangle triangle = Triangle(MAIN_WINDOW_NAME, DEFAULT_SHADER_NAME, point1, point2, point3);
    triangle.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    while (!WindowManager::Instance().isWindowClose(MAIN_WINDOW_NAME)) {
        WindowManager::Instance().clearWindow(MAIN_WINDOW_NAME);
        triangle.render();
        glfwPollEvents(); // This will be replaced by a event manager
    }

    ShaderManager::Instance().destroyShaders();
    WindowManager::Instance().terminate();

    return 0;
}
```

For more example code, you can see the [`test`](https://github.com/Zch720/SimpleGameLibrary/tree/main/simple_rendering/test) folder in SimpleRendering.
