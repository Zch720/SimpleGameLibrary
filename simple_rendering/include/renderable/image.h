#pragma once

#include <string>
#include <memory>
#include "./renderable.h"

class Image : public Renderable {
public:
    Image(const std::string & windowIdentifyName, const std::string & shaderIdentifyName, const std::string& path);
    ~Image();

    int width() const;
    int height() const;

protected:
    void renderImpl() const override;
    void loadData();
    bool isInvalidTextureType() const;

    uint32_t textureId;
    const std::string texturePath;
    std::shared_ptr<uint8_t> data;
    int widthVal;
    int heightVal;
    int channels;

    uint32_t VAO;
};
