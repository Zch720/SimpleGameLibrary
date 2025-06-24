#include "../../include/renderable/image.h"
#include <regex>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../../include/shader_manager.h"

Image::Image(WindowId windowId, ShaderId shaderId, const std::string & path) :
        Renderable(windowId, shaderId), texturePath(path) {
    loadData();

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthVal, heightVal, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get());
    glGenerateMipmap(GL_TEXTURE_2D);
    
    float halfWidth = widthVal / 2.0f;
    float halfHeight = heightVal / 2.0f;
    float vertices[30];
    vertices[0] = -halfWidth, vertices[1] = halfHeight, vertices[2] = 0.0f, vertices[3] = 0.0f, vertices[4] = 0.0f;
    vertices[5] = halfWidth, vertices[6] = halfHeight, vertices[7] = 0.0f, vertices[8] = 1.0f, vertices[9] = 0.0f;
    vertices[10] = halfWidth, vertices[11] = -halfHeight, vertices[12] = 0.0f, vertices[13] = 1.0f, vertices[14] = 1.0f;

    vertices[15] = -halfWidth, vertices[16] = halfHeight, vertices[17] = 0.0f, vertices[18] = 0.0f, vertices[19] = 0.0f;
    vertices[20] = halfWidth, vertices[21] = -halfHeight, vertices[22] = 0.0f, vertices[23] = 1.0f, vertices[24] = 1.0f;
    vertices[25] = -halfWidth, vertices[26] = -halfHeight, vertices[27] = 0.0f, vertices[28] = 0.0f, vertices[29] = 1.0f;

    uint32_t VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Image::~Image() {
}

int Image::width() const {
    return widthVal;
}

int Image::height() const {
    return heightVal;
}

void Image::renderImpl() const {
    glBindVertexArray(VAO);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
}

void Image::loadData() {
    if (!isInvalidTextureType()) {
        throw std::runtime_error("Unable to load texture file: " + texturePath + ". Invalid texture type.");
    }

    uint8_t * data = stbi_load(texturePath.c_str(), &widthVal, &heightVal, &channels, STBI_rgb_alpha);
    if (data == nullptr) {
        throw std::runtime_error("Unable to load texture file: " + texturePath);
    }

    this->data = std::shared_ptr<uint8_t>(new uint8_t[widthVal * heightVal * 4]);
    memcpy(this->data.get(), data, widthVal * heightVal * 4);
    stbi_image_free(data);
}

bool Image::isInvalidTextureType() const {
    std::regex textureRegex(".*\\.(bmp|jpg|png)$");
    return std::regex_search(texturePath.begin(), texturePath.end(), textureRegex);
}