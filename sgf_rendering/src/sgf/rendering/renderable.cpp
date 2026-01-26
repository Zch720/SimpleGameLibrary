#include "../../../include/sgf/rendering/renderable.h"
#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../../../include/sgf/rendering/render_context.h"

namespace sgf_core {
    const std::string RenderableTag::TypeName = "Renderable";
    const std::string Renderable::TypeName = "Renderable";

    Renderable::Renderable(const Id & id, const Construct & constructParameter):
            meshId(constructParameter.meshId),
            materialId(constructParameter.materialId),
            color(1.0f),
            positionValue(0.0f),
            scaleValue(1.0f),
            rotationValue(0.0f) {
        this->id = id;
        updateTransformationMatrix();
    }

    UniformProvider & Renderable::getUniformProvider() {
        return uniformProvider;
    }

    const UniformProvider & Renderable::getUniformProvider() const {
        return uniformProvider;
    }

    glm::vec4 Renderable::getColor() const {
        return color;
    }

    glm::mat4 Renderable::getTransformationMatrix() const {
        return transformationMatrix;
    }

    void Renderable::update() {
        if (transformDirty) {
            updateTransformationMatrix();
            transformDirty = false;
        }
    }

    void Renderable::render(const RenderContext & context) const {
        if (!context.MeshManager.isExist(meshId)) return;

        Material & material = context.MaterialManager.getRef(materialId);
        material.bind(context);
        material.applyPerObject(context, *this);

        Mesh & mesh = context.MeshManager.getRef(meshId);
        mesh.bind();
        glDrawElements(GL_TRIANGLES, mesh.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
        mesh.unbind();
    }

    void Renderable::setColor(float r, float g, float b, float a) {
        color = glm::vec4(r, g, b, a);
    }

    glm::vec3 Renderable::position() const {
        return positionValue;
    }

    void Renderable::position(const glm::vec3 & position) {
        positionValue = position;
        transformDirty = true;
    }

    void Renderable::translate(const glm::vec3 & translate) {
        positionValue += translate;
        transformDirty = true;
    }

    void Renderable::translateX(const float delta) {
        positionValue.x += delta;
        transformDirty = true;
    }

    void Renderable::translateY(const float delta) {
        positionValue.y += delta;
        transformDirty = true;
    }

    void Renderable::translateZ(const float delta) {
        positionValue.z += delta;
        transformDirty = true;
    }

    glm::vec3 Renderable::scale() const {
        return scaleValue;
    }

    void Renderable::scale(const glm::vec3 & scale) {
        scaleValue = scale;
        transformDirty = true;
    }

    void Renderable::scaleX(const float scale) {
        scaleValue.x = scale;
        transformDirty = true;
    }

    void Renderable::scaleY(const float scale) {
        scaleValue.y = scale;
        transformDirty = true;
    }

    void Renderable::scaleZ(const float scale) {
        scaleValue.z = scale;
        transformDirty = true;
    }

    glm::vec3 Renderable::rotation() const {
        return rotationValue;
    }

    void Renderable::rotation(const glm::vec3 & rotation) {
        rotationValue = rotation;
        transformDirty = true;
    }

    void Renderable::rotate(const glm::vec3 & rotate) {
        rotationValue += rotate;
        transformDirty = true;
    }

    void Renderable::rotateX(const float rotate) {
        rotationValue.x += rotate;
        transformDirty = true;
    }

    void Renderable::rotateY(const float rotate) {
        rotationValue.y += rotate;
        transformDirty = true;
    }

    void Renderable::rotateZ(const float rotate) {
        rotationValue.z += rotate;
        transformDirty = true;
    }

    void Renderable::updateTransformationMatrix() {
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat, glm::radians(rotationValue.x), glm::vec3(1.0f, 0.0f, 0.0f));
        mat = glm::rotate(mat, glm::radians(rotationValue.y), glm::vec3(0.0f, 1.0f, 0.0f));
        mat = glm::rotate(mat, glm::radians(rotationValue.z), glm::vec3(0.0f, 0.0f, 1.0f));
        mat = glm::translate(mat, positionValue);
        mat = glm::scale(mat, scaleValue);
        transformationMatrix = mat;
    }
}
