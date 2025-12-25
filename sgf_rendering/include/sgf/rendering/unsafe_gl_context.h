#pragma once

#include <glad/gl.h>
#include "./mesh_id.h"
#include "./shader_id.h"
#include "./texture_2d_id.h"

class RenderContext;

class UnsafeGLContext {
public:
    UnsafeGLContext() = delete;
    UnsafeGLContext(UnsafeGLContext &) = delete;
    UnsafeGLContext(const UnsafeGLContext &) = delete;
    UnsafeGLContext& operator=(UnsafeGLContext &) = delete;
    UnsafeGLContext& operator=(const UnsafeGLContext &) = delete;

    
    GLuint getShaderProgramHandle(const ShaderId & shaderId) const;

    GLuint getMeshVAO(const MeshId & meshId) const;
    GLuint getMeshVBO(const MeshId & meshId) const;
    GLuint getMeshEBO(const MeshId & meshId) const;

    GLuint getTexture2DTextureHandle(const Texture2DId & textureId) const;

private:
    friend RenderContext;

    UnsafeGLContext(RenderContext & renderContext);

    RenderContext & renderContext;
};