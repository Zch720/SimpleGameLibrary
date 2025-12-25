#pragma once

#include <stdint.h>
#include <string>
#include <resource.h>
#include "./texture_2d_id.h"

class Texture2D: public Resource<Texture2D, Texture2DId> {
public:
    struct Construct {
        std::string path;
    };

    Texture2D(const Id & id, const Construct & constructParameter);
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

#include "./texture_2d.tpp"
