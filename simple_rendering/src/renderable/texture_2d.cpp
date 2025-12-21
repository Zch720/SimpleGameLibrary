#include "../../include/renderable/texture_2d.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <memory>
#include <regex>

Texture2D::Texture2D(): path(""), textureId(0) {
}

Texture2D::Texture2D(const std::string & path): path(path) {
    uint8_t * data = loadData();

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    delete data;
}

Texture2D::~Texture2D() {
    if (textureId != 0) {
        glDeleteTextures(1, &textureId);
    }
}

std::string Texture2D::getPath() const {
    return path;
}

int Texture2D::getWidth() const {
    return width;
}

int Texture2D::getHeight() const {
    return height;
}

uint32_t Texture2D::getTextureId() const {
    return textureId;
}

void Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, textureId);
}

bool Texture2D::isInvalidTextureType() const {
    std::regex textureRegex(".*\\.(bmp|jpg|png)$");
    return std::regex_search(path.begin(), path.end(), textureRegex);
}

uint8_t * Texture2D::loadData() {
    if (!isInvalidTextureType()) {
        throw std::runtime_error("Unable to load texture file: " + path + ". Invalid texture type.");
    }

    uint8_t * data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    if (data == nullptr) {
        throw std::runtime_error("Unable to load texture file: " + path);
    }

    uint8_t * result = new uint8_t[width * height * 4];
    memcpy(result, data, width * height * 4);
    stbi_image_free(data);
    return result;
}