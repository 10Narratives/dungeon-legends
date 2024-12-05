#ifndef CORE_ECS_COMPONENT_BASE_H
#define CORE_ECS_COMPONENT_BASE_H

#include <memory>
namespace core::ecs {

/**
 * @struct ComponentBase
 * @brief A base class for all components in the ECS module.
 *
 * This class serves as a common interface for components in the ECS.
 * It provides virtual destruction to ensure proper resource management
 * when derived classes are deleted via a base class pointer.
 */
struct ComponentBase {
 public:
  /**
   * @brief Default constructor.
   *
   * Constructs a `ComponentBase` instance. This constructor does not perform
   * any special initialization.
   */
  ComponentBase() = default;

  /**
   * @brief Virtual destructor.
   *
   * Ensures derived classes are correctly destroyed when a `ComponentBase` pointer
   * is used to delete them.
   */
  virtual ~ComponentBase() = default;
};

/**
 * @typedef component_ptr
 * @brief Alias for a shared pointer to a `ComponentBase` instance.
 *
 * Simplifies the management and usage of dynamically allocated `ComponentBase` objects.
 */
using component_ptr = std::shared_ptr<ComponentBase>;

}  // namespace core::ecs

#endif
