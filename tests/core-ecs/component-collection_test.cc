#include "ecs/component-collection.h"
using core::ecs::ComponentCollection;

#include "ecs/component-base.h"
using core::ecs::ComponentBase;

struct Position final : public ComponentBase {
  Position() = default;
  Position(float x, float y) : x(x), y(y) {}

  float x{0}, y{0};
};

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("ComponentCollection Modifiers") {
  SECTION("Emplace()") {
    ComponentCollection collection;
    bool was_emplaced = collection.Emplace<Position>(1, 10);
    REQUIRE(was_emplaced == true);
    REQUIRE(collection.Size() == 1);
    REQUIRE(collection.Empty() == false);

    was_emplaced = collection.Emplace<Position>(100, 100);
    REQUIRE(was_emplaced == false);
    REQUIRE(collection.Size() == 1);
    REQUIRE(collection.Empty() == false);
  }
  SECTION("Erase()") {
    ComponentCollection collection;
    collection.Emplace<Position>(1, 10);
    bool was_erased = collection.Erase<Position>();
    REQUIRE(was_erased == true);
    REQUIRE(collection.Size() == 0);
    REQUIRE(collection.Empty() == true);
  }
  SECTION("Extract()") {
    ComponentCollection collection;
    collection.Emplace<Position>();
    auto extracted = collection.Extract<Position>();
    REQUIRE(extracted != nullptr);
    REQUIRE(collection.Size() == 0);
    REQUIRE(collection.Empty() == true);
  }
}
