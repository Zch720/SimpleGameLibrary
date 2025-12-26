#include "../../../include/sgf/rendering/texture_2d.h"
#include <glad/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <memory>
#include <regex>

namespace sgf_core {
    const std::string Texture2DTag::TypeName = "Texture2D";
    const std::string Texture2D::TypeName = "Texture2D";

    Texture2D::Texture2D(const Id & id, const Construct & constructParameter): path(constructParameter.path) {
        this->id = id;

        uint8_t * data = loadData();

        glGenTextures(1, &textureHandle);
        glBindTexture(GL_TEXTURE_2D, textureHandle);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        delete[] data;
    }

    Texture2D::~Texture2D() {
        if (textureHandle != 0) {
            glDeleteTextures(1, &textureHandle);
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

    void Texture2D::bind() const {
        glBindTexture(GL_TEXTURE_2D, textureHandle);
    }

    bool Texture2D::isValidTextureType() const {
        std::regex textureRegex(".*\\.(bmp|jpg|png)$");
        return std::regex_search(path.begin(), path.end(), textureRegex);
    }

    uint8_t * Texture2D::loadData() {
        if (!isValidTextureType()) {
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
}
