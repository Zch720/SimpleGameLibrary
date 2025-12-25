#include "../../../include/sgf/rendering/unsafe_gl_context.h"
#include "../../../include/sgf/rendering/render_context.h"

UnsafeGLContext::UnsafeGLContext(RenderContext & renderContext): renderContext(renderContext) {
}

GLuint UnsafeGLContext::getShaderProgramHandle(const ShaderId & shaderId) const {
    return renderContext.ShaderManager.getRef(shaderId).programHandle;
}

GLuint UnsafeGLContext::getMeshVAO(const MeshId & meshId) const {
    return renderContext.MeshManager.getRef(meshId).VAO;
}

GLuint UnsafeGLContext::getMeshVBO(const MeshId & meshId) const {
    return renderContext.MeshManager.getRef(meshId).VBO;
}

GLuint UnsafeGLContext::getMeshEBO(const MeshId & meshId) const {
    return renderContext.MeshManager.getRef(meshId).EBO;
}

GLuint UnsafeGLContext::getTexture2DTextureHandle(const Texture2DId & id) const {
    return renderContext.Texture2DManager.getRef(id).textureHandle;
}
