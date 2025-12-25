#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include "./type_name.h"

template <typename Id>
class IdGenerator;

template <typename Tag>
class ResourceId {
public:
    ResourceId();

    uint32_t getId() const;
    uint32_t getGen() const;

    std::string toString() const;

    static std::string getTypeName();

    bool operator==(const ResourceId<Tag> & other) const noexcept;
    bool operator!=(const ResourceId<Tag> & other) const noexcept;

protected:
    ResourceId(uint32_t id, uint32_t gen);

private:
    friend IdGenerator<ResourceId<Tag>>;

    uint32_t id;
    uint32_t gen;
};

namespace std {
    template <typename Tag>
    struct hash<ResourceId<Tag>> {
        size_t operator()(const ResourceId<Tag> & id) const noexcept;
    };
    template <typename Tag>
    struct equal_to<ResourceId<Tag>> {
        bool operator()(const ResourceId<Tag> & left, const ResourceId<Tag> & right) const noexcept;
    };
}

#include "./resource_id.tpp"
