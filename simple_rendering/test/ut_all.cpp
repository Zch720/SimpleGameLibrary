#include <gtest/gtest.h>

#include "window_test.h"
#include "window_manager_test.h"
#include "shader_test.h"
#include "shader_manager_test.h"
#include "shape_triangle_test.h"
#include "shape_rectangle_test.h"
#include "shape_polygon_test.h"
#include "shape_test.h"

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}