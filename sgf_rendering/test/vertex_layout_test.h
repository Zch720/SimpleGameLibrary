#include <gtest/gtest.h>
#include "../include/vertex_layout.h"

TEST(VertexLayoutSuite, AddStride_GL_BYTE) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_BYTE, .normalized = false, .offset = 0 });

    ASSERT_EQ(1, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_GL_UNSIGNED_BYTE) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_UNSIGNED_BYTE, .normalized = false, .offset = 0 });

    ASSERT_EQ(1, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_GL_SHORT) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_SHORT, .normalized = false, .offset = 0 });

    ASSERT_EQ(2, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_GL_UNSIGNED_SHORT) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_UNSIGNED_SHORT, .normalized = false, .offset = 0 });

    ASSERT_EQ(2, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_GL_INT) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_INT, .normalized = false, .offset = 0 });

    ASSERT_EQ(4, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_GL_UNSIGNED_INT) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_UNSIGNED_INT, .normalized = false, .offset = 0 });

    ASSERT_EQ(4, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_GL_HALF_FLOAT) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_HALF_FLOAT, .normalized = false, .offset = 0 });

    ASSERT_EQ(2, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_GL_FLOAT) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_FLOAT, .normalized = false, .offset = 0 });

    ASSERT_EQ(4, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_GL_DOUBLE) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_DOUBLE, .normalized = false, .offset = 0 });

    ASSERT_EQ(8, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_GL_INT_2_10_10_10_REV) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_INT_2_10_10_10_REV, .normalized = false, .offset = 0 });

    ASSERT_EQ(4, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_GL_UNSIGNED_INT_2_10_10_10_REV) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_UNSIGNED_INT_2_10_10_10_REV, .normalized = false, .offset = 0 });

    ASSERT_EQ(4, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_GL_UNSIGNED_INT_10F_11F_11F_REV) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 1, .type = GL_UNSIGNED_INT_10F_11F_11F_REV, .normalized = false, .offset = 0 });

    ASSERT_EQ(4, vertexLayout.getStride());
}

TEST(VertexLayoutSuite, AddStride_MultipleTypes) {
    VertexLayout vertexLayout;

    vertexLayout.addAttribute({ .index = 0, .size = 2, .type = GL_BYTE, .normalized = false, .offset = 0 });
    vertexLayout.addAttribute({ .index = 1, .size = 3, .type = GL_FLOAT, .normalized = false, .offset = 2 * sizeof(int8_t) });
    vertexLayout.addAttribute({ .index = 2, .size = 1, .type = GL_INT, .normalized = false, .offset = 2 * sizeof(int8_t) + 3 * sizeof(float) });

    ASSERT_EQ(18, vertexLayout.getStride());
}