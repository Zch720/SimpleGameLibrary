#pragma once

#include <stdint.h>
#include <string>

class Texture2D {
public:
    Texture2D();
    Texture2D(const std::string & path);
    ~Texture2D();

    std::string getPath() const;
    int getWidth() const;
    int getHeight() const;

    uint32_t getTextureId() const;

    void bind() const;

private:
    std::string path;

    int width;
    int height;
    int channels;

    uint32_t textureId;

    bool isValidTextureType() const;
    uint8_t * loadData();
};
