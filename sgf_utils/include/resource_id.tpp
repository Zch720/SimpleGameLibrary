#include "./resource_id.h"

template <typename Tag>
ResourceId<Tag>::ResourceId(): id(0), gen(0) {
}

template <typename Tag>
ResourceId<Tag>::ResourceId(uint32_t id, uint32_t gen): id(id), gen(gen) {
}

template <typename Tag>
uint32_t ResourceId<Tag>::getId() const {
    return id;
}

template <typename Tag>
uint32_t ResourceId<Tag>::getGen() const {
    return gen;
}

template <typename Tag>
std::string ResourceId<Tag>::toString() const {
    return getTypeName() + "Id(id=" + std::to_string(id) + ", gen=" + std::to_string(gen) + ")";
}

template <typename Tag>
std::string ResourceId<Tag>::getTypeName() {
    typename TypeName<Tag>::TypeName typeNameObj;
    return typeNameObj();
}

template <typename Tag>
bool ResourceId<Tag>::operator==(const ResourceId<Tag> & other) const noexcept {
    return id == other.id && gen == other.gen;
}

template <typename Tag>
bool ResourceId<Tag>::operator!=(const ResourceId<Tag> & other) const noexcept {
    return id != other.id || gen != other.gen;
}

namespace std {
    template <typename Tag>
    size_t hash<ResourceId<Tag>>::operator()(const ResourceId<Tag> & id) const noexcept {
        return ((size_t)id.getGen()) << 32 | id.getId();
    }

    template <typename Tag>
    bool equal_to<ResourceId<Tag>>::operator()(const ResourceId<Tag> & left, const ResourceId<Tag> & right) const noexcept {
        return left.getId() == right.getId() && left.getGen() == right.getGen();
    }
}
