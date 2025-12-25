#pragma once

#include <stdint.h>
#include <string>
#include <resource.h>
#include "./texture_2d_id.h"

class UnsafeGLContext;

class Texture2D: public Resource<Texture2D, Texture2DId> {
public:
    static const std::string TypeName;
    struct Construct {
        std::string path;
    };

    Texture2D(const Id & id, const Construct & constructParameter);
    ~Texture2D();

    std::string getPath() const;
    int getWidth() const;
    int getHeight() const;

    void bind() const;

private:
    friend UnsafeGLContext;

    std::string path;

    int width;
    int height;
    int channels;

    uint32_t textureHandle;

    bool isValidTextureType() const;
    uint8_t * loadData();
};
