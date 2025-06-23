#pragma once

#include <string>
#include <memory>
#include "./renderable.h"

class ShaderId;
class Window;

class Image : public Renderable {
public:
    friend Window;

    ~Image();

    int width() const;
    int height() const;

protected:
    Image(const std::string & windowIdentifyName, ShaderId shaderId, const std::string& path);

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
