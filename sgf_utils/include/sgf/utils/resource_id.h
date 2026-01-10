#pragma once

#include <cstdint>
#include <functional>
#include <string>

namespace sgf_core {
    template <typename Id>
    class IdGenerator;

    template <typename Tag>
    class ResourceId {
    public:
        ResourceId();

        bool isDefault() const;

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
}

namespace std {
    template <typename Tag>
    struct hash<sgf_core::ResourceId<Tag>> {
        size_t operator()(const sgf_core::ResourceId<Tag> & id) const noexcept;
    };
    template <typename Tag>
    struct equal_to<sgf_core::ResourceId<Tag>> {
        bool operator()(const sgf_core::ResourceId<Tag> & left, const sgf_core::ResourceId<Tag> & right) const noexcept;
    };
}

#include "./resource_id.tpp"
