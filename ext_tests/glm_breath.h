#include <gtest/gtest.h>
#include <glm/matrix.hpp>

TEST(GlmSuite, Breath) {
    glm::mat4 matrix(1.0f);
    EXPECT_EQ(matrix[0][0], 1.0f);
    EXPECT_EQ(matrix[1][1], 1.0f);
    EXPECT_EQ(matrix[2][2], 1.0f);
    EXPECT_EQ(matrix[3][3], 1.0f);
}