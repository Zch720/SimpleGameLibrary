#include <gtest/gtest.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "./glfw_breath.h"
#include "./glm_breath.h"

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}