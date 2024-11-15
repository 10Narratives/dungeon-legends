#ifndef CORE_ECS_ARCHETYPE_H
#define CORE_ECS_ARCHETYPE_H

#include "ecs/component-collection.h"
#include "type-traits.h"

namespace core::ecs {

/**
 * @defgroup ecs ECS
 * @brief Entity-Component-System (ECS) module.
 */

/**
 * @ingroup ecs
 * @brief A template class that defines an Archetype within an ECS system.
 *
 * The `Archetype` class template manages a set of required component types for an entity.
 * It provides methods for verifying component presence, creating component collections,
 * and supplementing collections with missing components as specified by the Archetype.
 *
 * @tparam RequiredComponentTypes Variadic template parameter pack representing the required component types.
 */
template <is_component... RequiredComponentTypes>
class Archetype final {
 public:
  /**
   * @brief Checks if all required component types are present in the specified component collection.
   *
   * This method verifies whether the provided `ComponentCollection` instance contains
   * all component types required by this Archetype.
   *
   * @param[in] collection The component collection to check.
   * @return `true` if all required component types are present, `false` otherwise.
   */
  [[nodiscard]] static bool IsPresentedIn(const ComponentCollection& collection) noexcept;

  /**
   * @brief Creates a new component collection containing all required component types.
   *
   * Constructs a new `ComponentCollection` instance and populates it with instances of all
   * component types specified by this Archetype.
   *
   * @return A new `ComponentCollection` instance containing all required components.
   */
  [[nodiscard]] static ComponentCollection CreateInstance();

  /**
   * @brief Ensures the specified component collection contains all required component types.
   *
   * This method supplements the provided `ComponentCollection` by adding any missing
   * component types that are required by this Archetype.
   *
   * @param[in,out] collection The component collection to supplement with missing components.
   * @return `true` if all missing components are successfully added, `false` otherwise.
   */
  [[maybe_unused]] static bool Supplement(ComponentCollection& collection);
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
