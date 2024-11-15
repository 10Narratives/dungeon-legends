#ifndef CORE_ECS_COMPONENT_COLLECTION_H
#define CORE_ECS_COMPONENT_COLLECTION_H

#include <cstddef>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "component-base.h"
#include "type-traits.h"

namespace core::ecs {

/**
 * @defgroup ecs ECS
 * @brief Entity-Component-System (ECS) module.
 */

/**
 * @ingroup ecs
 * @brief A collection of components indexed by their type.
 *
 * Manages components using a type-indexed map, allowing storage, retrieval, and manipulation
 * of components based on their type. This class ensures type safety and provides efficient
 * access to components.
 */
class ComponentCollection final {
 public:
  /// @{
  /**
   * @name Constructors
   */

  /**
   * @brief Constructs an empty ComponentCollection.
   */
  ComponentCollection() = default;

  /**
   * @brief Copy constructor.
   *
   * Creates a deep copy of another ComponentCollection, copying all components.
   *
   * @param other The collection to copy from.
   */
  ComponentCollection(const ComponentCollection& other);

  /**
   * @brief Copy assignment operator.
   *
   * Replaces the contents of this collection with those of another collection.
   *
   * @param other The collection to copy from.
   * @return Reference to the updated collection.
   */
  ComponentCollection& operator=(const ComponentCollection& other);
  /// @}

  /// @{
  /**
   * @name Capacity
   */

  /**
   * @brief Checks if the collection is empty.
   *
   * @return `true` if the collection contains no components, otherwise `false`.
   */
  [[nodiscard]] bool Empty() const noexcept;

  /**
   * @brief Returns the number of components in the collection.
   *
   * @return The number of components in the collection.
   */
  [[nodiscard]] std::size_t Size() const noexcept;

  /**
   * @brief Removes all components from the collection.
   */
  void Clear();
  /// @}

  /// @{
  /**
   * @name Modifiers
   */

  /**
   * @brief Adds a component to the collection.
   *
   * @tparam ComponentType The type of the component to add.
   * @tparam Args Argument types for the component's constructor.
   * @param arguments Arguments to forward to the component's constructor.
   * @return `true` if the component was successfully added, otherwise `false`.
   *
   * @note If a component of the same type already exists, it will not be replaced.
   */
  template <is_component ComponentType, typename... Args>
  [[maybe_unused]] bool Emplace(Args&&... arguments);

  /**
   * @brief Removes a component from the collection.
   *
   * @tparam ComponentType The type of the component to remove.
   * @return `true` if the component was successfully removed, otherwise `false`.
   */
  template <is_component ComponentType>
  [[maybe_unused]] bool Erase();

  /**
   * @brief Extracts a component from the collection.
   *
   * @tparam ComponentType The type of the component to extract.
   * @return A shared pointer to the extracted component, or `nullptr` if the component is not found.
   */
  template <is_component ComponentType>
  [[nodiscard]] component_ptr Extract();
  /// @}

  /// @{
  /**
   * @name Lookup
   */

  /**
   * @brief Retrieves a weak pointer to a component in the collection.
   *
   * @tparam ComponentType The type of the component to retrieve.
   * @return A weak pointer to the component, or an empty weak pointer if the component is not found.
   */
  template <is_component ComponentType>
  [[nodiscard]] std::weak_ptr<ComponentType> Get();

  /**
   * @brief Checks if the collection contains all specified component types.
   *
   * @tparam ComponentTypes The types of components to check.
   * @return `true` if all specified components are present, otherwise `false`.
   */
  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAll() const noexcept;

  /**
   * @brief Checks if the collection contains any of the specified component types.
   *
   * @tparam ComponentTypes The types of components to check.
   * @return `true` if at least one of the specified components is present, otherwise `false`.
   */
  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAny() const noexcept;
  /// @}

 private:
  /// Stores components indexed by their type using std::type_index as the key.
  std::unordered_map<std::type_index, component_ptr> inner_components_;
};

}  // namespace core::ecs

#endif
