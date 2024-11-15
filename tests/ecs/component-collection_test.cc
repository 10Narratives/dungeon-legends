#include "ecs/component-collection.h"
using core::ecs::ComponentCollection;

#include "ecs/component-base.h"
using core::ecs::ComponentBase;

struct Position final : public ComponentBase {
 public:
  Position() = default;
  Position(float x, float y) : x(x), y(y) {}

  float x{0}, y{0};
};

struct Velocity final : public ComponentBase {
 public:
  Velocity() = default;
  Velocity(float x, float y) : vx(x), vy(y) {}

  float vx{0}, vy{0};
};

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("ComponentCollection TemplateMethods") {
  ComponentCollection collection;
  SECTION("Emplace") {
    collection.Emplace<Position>(10, 10);
    auto stored_pos = collection.Get<Position>().lock();
    REQUIRE(stored_pos->x == 10);
    REQUIRE(stored_pos->y == 10);
  }
  SECTION("Erase") {
    collection.Emplace<Position>(10, 10);
    REQUIRE(collection.Erase<Position>() == true);
  }
  SECTION("Extract") {
    collection.Emplace<Position>(10, 10);
    auto extracted = collection.Extract<Position>();
    REQUIRE(collection.Size() == 0);
  }
  SECTION("Query methods") {
    collection.Emplace<Position>(10, 10);
    REQUIRE(collection.HasAny<Position, Velocity>() == true);
    collection.Emplace<Velocity>(10, 10);
    REQUIRE(collection.HasAll<Position, Velocity>() == true);
  }
}
