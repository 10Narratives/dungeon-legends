#ifndef CORE_ECS_ARCHETYPE_H
#define CORE_ECS_ARCHETYPE_H

#include "ecs/component-collection.h"
#include "ecs/type-traits.h"
namespace core::ecs {

template <is_component... RequiredComponents>
class Archetype final {
 public:
  [[nodiscard]] static ComponentCollection CreateInstance();

  [[maybe_unused]] static bool Supplement(ComponentCollection& collection);

  [[nodiscard]] static bool IsPresentedIn(const ComponentCollection& collection) noexcept;
};

template <is_component... RequiredComponentTypes>
bool Archetype<RequiredComponentTypes...>::IsPresentedIn(const ComponentCollection& collection) noexcept {
  return collection.HasAll<RequiredComponentTypes...>();
}

template <is_component... RequiredComponentTypes>
ComponentCollection Archetype<RequiredComponentTypes...>::CreateInstance() {
  ComponentCollection new_instance;
  (new_instance.Emplace<RequiredComponentTypes>(), ...);
  return new_instance;
}

template <is_component... RequiredComponentTypes>
bool Archetype<RequiredComponentTypes...>::Supplement(ComponentCollection& collection) {
  return (collection.Emplace<RequiredComponentTypes>() && ...);
}

}  // namespace core::ecs

#endif
