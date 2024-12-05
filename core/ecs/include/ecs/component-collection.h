#ifndef CORE_ECS_COMPONENT_COLLECTION_H
#define CORE_ECS_COMPONENT_COLLECTION_H

#include <cstddef>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "component-base.h"
#include "type-traits.h"
namespace core::ecs {

/**
 * @class ComponentCollection
 * @brief Manages a collection of components in an ECS framework.
 *
 * The `ComponentCollection` class allows adding, removing, and querying components
 * by type, ensuring type-safe operations in an entity-component system.
 */
class ComponentCollection final {
 public:
  // Constructors
  /**
   * @brief Default constructor.
   *
   * Initializes an empty `ComponentCollection`.
   */
  ComponentCollection() = default;

  /**
   * @brief Copy constructor for `ComponentCollection`.
   *
   * Creates a deep copy of the given `ComponentCollection` instance. Each component in the
   * source collection is cloned and added to the new collection.
   *
   * @param other The `ComponentCollection` to copy from.
   */
  ComponentCollection(const ComponentCollection& other);

  /**
   * @brief Copy assignment operator for `ComponentCollection`.
   *
   * Replaces the contents of this `ComponentCollection` with a deep copy of the given
   * `ComponentCollection`. All existing components in this collection are cleared, and
   * new components are cloned from the source collection.
   *
   * @param other The `ComponentCollection` to copy from.
   * @return A reference to this `ComponentCollection`.
   */
  ComponentCollection& operator=(const ComponentCollection& other);

  // Capacity
  /**
   * @brief Returns the number of components in the collection.
   *
   * @return The number of components currently stored.
   */
  [[nodiscard]] std::size_t Size() const noexcept;

  /**
   * @brief Checks if the collection is empty.
   *
   * @return `true` if the collection has no components; otherwise, `false`.
   */
  [[nodiscard]] bool Empty() const noexcept;

  // Modifiers
  /**
   * @brief Removes all components from the collection.
   */
  void Clear();

  /**
   * @brief Adds a new component of the specified type to the collection.
   *
   * Constructs a new component of type `ComponentType` using the provided arguments and
   * inserts it into the collection. If a component of the same type already exists in
   * the collection, the insertion fails, and the method returns `false`.
   *
   * @tparam ComponentType The type of the component to add. This must satisfy the `is_component` constraint.
   * @tparam Args The types of the arguments used to construct the component.
   * @param arguments The arguments to pass to the constructor of `ComponentType`.
   * @return `true` if the component was successfully added to the collection; otherwise, `false`.
   *
   * @note
   * This method ensures that only one instance of a specific component type can exist in
   * the collection. Attempting to add a component of the same type will not overwrite
   * the existing component.
   *
   * @warning
   * The `ComponentType` must be constructible with the provided arguments. If the
   * construction fails, this method will result in a compilation error.
   */
  template <is_component ComponentType, typename... Args>
  [[maybe_unused]] bool Emplace(Args&&... arguments);

  /**
   * @brief Removes and returns a component of the specified type from the collection.
   *
   * Searches the collection for a component of type `ComponentType`. If found, the component
   * is removed from the collection and returned. If no such component exists, the method
   * returns `nullptr`.
   *
   * @tparam ComponentType The type of the component to extract. This must satisfy the `is_component` constraint.
   * @return A `std::shared_ptr` to the extracted component if it exists; otherwise, `nullptr`.
   *
   * @note
   * After calling this method, the collection no longer holds the extracted component.
   * This method transfers ownership of the component to the caller.
   *
   * @warning
   * Ensure that the caller properly manages the lifetime of the returned component. If the
   * component is not used or stored, it will be destroyed when the shared pointer goes out
   * of scope.
   *
   * @example
   * ```cpp
   * core::ecs::ComponentCollection collection;
   * // Add components...
   * auto my_component = collection.Extract<MyComponent>();
   * if (my_component) {
   *     // Use the extracted component.
   * }
   * ```
   */
  template <is_component ComponentType>
  [[nodiscard]] component_ptr Extract();

  /**
   * @brief Removes a component of the specified type from the collection.
   *
   * Searches the collection for a component of type `ComponentType` and removes it
   * if found. The method returns `true` if the component was successfully removed;
   * otherwise, it returns `false`.
   *
   * @tparam ComponentType The type of the component to erase. This must satisfy the `is_component` constraint.
   * @return `true` if the component was found and removed; `false` if no such component exists in the collection.
   *
   * @note
   * The method does not delete the component. Instead, it removes the component from
   * the collection and allows it to be properly destroyed based on the ownership
   * semantics of `std::shared_ptr`.
   *
   * @example
   * ```cpp
   * core::ecs::ComponentCollection collection;
   * // Add components...
   * bool success = collection.Erase<MyComponent>();
   * if (success) {
   *     // Component was successfully removed.
   * }
   * ```
   */
  template <is_component ComponentType>
  [[maybe_unused]] bool Erase();

  // Lookup
  /**
   * @brief Retrieves a weak pointer to a component of the specified type from the collection.
   *
   * Searches the collection for a component of type `ComponentType`. If found, the method
   * returns a `std::weak_ptr` to the component, which does not affect the component's
   * reference count. If no such component exists, the method returns an empty `std::weak_ptr`.
   *
   * @tparam ComponentType The type of the component to retrieve. This must satisfy the `is_component` constraint.
   * @return A `std::weak_ptr<ComponentType>` pointing to the component if found; otherwise, an empty `std::weak_ptr`.
   *
   * @note
   * The returned `std::weak_ptr` can be used to safely check for the existence of the component
   * and to access it if still valid. However, it does not keep the component alive.
   * Use `lock()` to obtain a `std::shared_ptr` if necessary.
   *
   * @example
   * ```cpp
   * core::ecs::ComponentCollection collection;
   * // Add components...
   * std::weak_ptr<MyComponent> weak_component = collection.Get<MyComponent>();
   * if (auto shared_component = weak_component.lock()) {
   *     // Component is still alive and can be used.
   * } else {
   *     // Component was removed or not found.
   * }
   * ```
   */
  template <is_component ComponentType>
  std::weak_ptr<ComponentType> Get();

  // Component Queries
  /**
   * @brief Checks if the collection contains all the specified component types.
   *
   * This method checks if the collection contains components of all the types specified
   * in the parameter pack `ComponentTypes`. It returns `true` if every type in the pack
   * is present in the collection, and `false` if any type is missing.
   *
   * @tparam ComponentTypes The types of the components to check for in the collection.
   * @return `true` if the collection contains all the specified component types; otherwise, `false`.
   *
   * @note
   * This method uses fold expressions to check each component type in the parameter pack
   * against the collection, ensuring that all components are present.
   *
   * @example
   * ```cpp
   * core::ecs::ComponentCollection collection;
   * // Add components...
   * bool has_all_components = collection.HasAll<MyComponent, AnotherComponent>();
   * if (has_all_components) {
   *     // Collection contains both MyComponent and AnotherComponent.
   * }
   * ```
   */
  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAll() const noexcept;

  /**
   * @brief Checks if the collection contains at least one of the specified component types.
   *
   * This method checks if the collection contains at least one component of the types specified
   * in the parameter pack `ComponentTypes`. It returns `true` if any of the specified types are
   * present in the collection, and `false` if none of them are found.
   *
   * @tparam ComponentTypes The types of the components to check for in the collection.
   * @return `true` if the collection contains at least one of the specified component types; otherwise, `false`.
   *
   * @note
   * This method uses fold expressions to check if at least one of the component types exists
   * in the collection.
   *
   * @example
   * ```cpp
   * core::ecs::ComponentCollection collection;
   * // Add components...
   * bool has_any_component = collection.HasAny<MyComponent, AnotherComponent>();
   * if (has_any_component) {
   *     // Collection contains at least one of MyComponent or AnotherComponent.
   * }
   * ```
   */
  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAny() const noexcept;

 private:
  std::unordered_map<std::type_index, component_ptr> inner_components_;
};

template <is_component ComponentType, typename... Args>
[[maybe_unused]] bool ComponentCollection::Emplace(Args&&... arguments) {
  auto new_component = std::make_shared<ComponentType>(std::forward<Args>(arguments)...);
  return inner_components_.try_emplace(typeid(ComponentType), std::move(new_component)).second;
}

template <is_component ComponentType>
component_ptr ComponentCollection::Extract() {
  std::shared_ptr<ComponentBase> extracted_component{nullptr};
  if (inner_components_.contains(typeid(ComponentType))) {
    auto node = inner_components_.extract(typeid(ComponentType));
    extracted_component = std::move(node.mapped());
  }
  return extracted_component;
}

template <is_component ComponentType>
bool ComponentCollection::Erase() {
  return inner_components_.erase(typeid(ComponentType)) > 0;
}

template <is_component ComponentType>
std::weak_ptr<ComponentType> ComponentCollection::Get() {
  std::shared_ptr<ComponentType> found_component{nullptr};
  auto iter = inner_components_.find(typeid(ComponentType));
  if (iter != inner_components_.end()) {
    found_component = std::dynamic_pointer_cast<ComponentType>(iter->second);
  }
  return found_component;
}

template <is_component... ComponentTypes>
bool ComponentCollection::HasAll() const noexcept {
  return (inner_components_.contains(typeid(ComponentTypes)) && ...);
}

template <is_component... ComponentTypes>
bool ComponentCollection::HasAny() const noexcept {
  return (inner_components_.contains(typeid(ComponentTypes)) || ...);
}

}  // namespace core::ecs

#endif
