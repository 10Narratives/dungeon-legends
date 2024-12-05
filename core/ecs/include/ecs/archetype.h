#ifndef CORE_ECS_ARCHETYPE_H
#define CORE_ECS_ARCHETYPE_H

#include "ecs/component-collection.h"
#include "ecs/type-traits.h"
namespace core::ecs {

/**
 * @brief Represents an archetype of required components in an Entity-Component-System (ECS) framework.
 *
 * This class defines an archetype consisting of a set of required components. It provides methods
 * for creating instances of component collections, checking if a collection contains the required
 * components, and supplementing existing collections with the necessary components.
 *
 * @tparam RequiredComponents A variadic template parameter pack that specifies the types of components
 *                            required for the archetype.
 */
template <is_component... RequiredComponents>
class Archetype final {
 public:
  /**
   * @brief Creates a new `ComponentCollection` instance containing all required components for this archetype.
   *
   * This static method creates a new instance of `ComponentCollection` and attempts to emplace all the
   * required components for the archetype. It returns the newly created collection.
   *
   * @return A `ComponentCollection` instance containing the required components for this archetype.
   *
   * @example
   * ```cpp
   * using Placeable = Archetype<Position, Scale>;
   * ComponentCollection instance = Placeable::CreateInstance();
   * // 'instance' now contains Position and Scale components.
   * ```
   */
  [[nodiscard]] static ComponentCollection CreateInstance();

  /**
   * @brief Supplements an existing collection with the required components for this archetype.
   *
   * This static method attempts to emplace all required components into the provided `ComponentCollection`.
   * It returns `true` if all components were successfully added, otherwise `false`.
   *
   * @param collection The collection to be supplemented with the required components.
   * @return `true` if all components were successfully added to the collection; otherwise, `false`.
   *
   * @example
   * ```cpp
   * using Placeable = Archetype<Position, Scale>;
   * ComponentCollection collection;
   * bool success = Placeable::Supplement(collection);
   * // 'success' is true if Position and Scale components were added to 'collection'.
   * ```
   */
  [[maybe_unused]] static bool Supplement(ComponentCollection& collection);

  /**
   * @brief Checks if the specified collection contains all required components for this archetype.
   *
   * This static method checks if the provided `ComponentCollection` contains all the components required by
   * the archetype. It returns `true` if all required components are present, and `false` otherwise.
   *
   * @param collection The collection to check.
   * @return `true` if the collection contains all required components; otherwise, `false`.
   *
   * @example
   * ```cpp
   * using Placeable = Archetype<Position, Scale>;
   * bool is_present = Placeable::IsPresentedIn(collection);
   * // 'is_present' is true if 'collection' contains both Position and Scale components.
   * ```
   */
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
