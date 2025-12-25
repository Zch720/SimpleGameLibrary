#include <gtest/gtest.h>
#include "../include/manager.h"
#include "../include/resource.h"
#include "./util.hpp"

struct FooTag {};
using FooId = ResourceId<FooTag>;

template <>
struct TypeName<FooTag> {
    std::string operator()() {
        return "Foo";
    }
};

class Foo : public Resource<Foo, FooId> {
public:
    struct Construct {
        int a;
    };

    Foo(const FooId & id, const Construct & constructParameter) {
        this->id = id;
        a = constructParameter.a;
    }

    int a;
};

template <>
struct TypeName<Foo> {
    std::string operator()() {
        return "Foo";
    }
};

TEST(ManagerSuite, CreateManager) {
    ASSERT_NO_THROW(Manager<Foo>());
}

TEST(ManagerSuite, CreateOneItem) {
    Manager<Foo> manager;

    FooId id = manager.create(Foo::Construct { .a = 100 });

    ASSERT_EQ(100, manager.getRef(id).a);
}

TEST(ManagerSuite, FindAnExistItem) {
    Manager<Foo> manager;

    FooId id = manager.create(Foo::Construct { .a = 100 });

    ASSERT_TRUE(manager.isExist(id));
}

TEST(ManagerSuite, FindAnNotExistItem) {
    Manager<Foo> manager;

    manager.create(Foo::Construct {.a = 100});

    ASSERT_FALSE(manager.isExist(FooId()));
}

TEST(ManagerSuite, CreateTwoItemShouldHasDifferentId) {
    Manager<Foo> manager;

    FooId id1 = manager.create(Foo::Construct { .a = 1 });
    FooId id2 = manager.create(Foo::Construct { .a = 2 });

    ASSERT_NE(id1, id2);
}

TEST(ManagerSuite, CreateTwoItemAndGetCorretItem) {
    Manager<Foo> manager;

    FooId id1 = manager.create(Foo::Construct { .a = 1 });
    FooId id2 = manager.create(Foo::Construct { .a = 2 });

    ASSERT_EQ(1, manager.getRef(id1).a);
    ASSERT_EQ(2, manager.getRef(id2).a);
}

TEST(ManagerSuite, RemoveItem) {
    Manager<Foo> manager;
    FooId id = manager.create(Foo::Construct { .a = 1 });

    ASSERT_NO_THROW(manager.remove(id));
}

TEST(ManagerSuite, RemovedItemShouldNotBeFound) {
    Manager<Foo> manager;
    FooId id = manager.create(Foo::Construct { .a = 1 });

    manager.remove(id);
    
    ASSERT_FALSE(manager.isExist(id));
}

TEST(ManagerSuite, DestroyAll) {
    Manager<Foo> manager;
    FooId id1 = manager.create(Foo::Construct { .a = 1 });
    FooId id2 = manager.create(Foo::Construct { .a = 2 });

    manager.destroyAll();

    ASSERT_FALSE(manager.isExist(id1));
    ASSERT_FALSE(manager.isExist(id2));
}

TEST(ManagerSuite, GetItemNotExist) {
    Manager<Foo> manager;

    ASSERT_THROW_MESSAGE(
        manager.getRef(FooId()),
        sgf::ResourceNotFound,
        "Try to get Foo with id FooId(id=0, gen=0) from manager, but not found"
    );
}

TEST(ManagerSuite, RemoveItemNotExist) {
    Manager<Foo> manager;

    ASSERT_THROW_MESSAGE(
        manager.remove(FooId()),
        sgf::ResourceNotFound,
        "Try to remove Foo with id FooId(id=0, gen=0) in manager, but not found"
    );
}