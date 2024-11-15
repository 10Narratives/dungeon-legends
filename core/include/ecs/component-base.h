#ifndef CORE_ECS_COMPONENT_BASE_H
#define CORE_ECS_COMPONENT_BASE_H

#include <memory>

namespace core::ecs {

/**
 * @defgroup ecs ECS
 * @brief Entity-Component-System (ECS) module.
 */

/**
 * @ingroup ecs
 * @brief Base class for all components in the ECS system.
 *
 * The `ComponentBase` class serves as the base type for all components in the ECS framework.
 * It provides a common interface and ensures polymorphic behavior for derived components.
 */
struct ComponentBase {
 public:
  /**
   * @brief Default constructor.
   *
   * Initializes a new instance of `ComponentBase`.
   */
  ComponentBase() = default;

  /**
   * @brief Virtual destructor.
   *
   * Ensures proper cleanup of derived components when deleted through a `ComponentBase` pointer.
   */
  virtual ~ComponentBase() = default;
};

/**
 * @ingroup ecs
 * @brief Alias for a shared pointer to `ComponentBase`.
 *
 * `component_ptr` is used to manage components with shared ownership in the ECS system.
 */
using component_ptr = std::shared_ptr<ComponentBase>;

}  // namespace core::ecs

#endif
