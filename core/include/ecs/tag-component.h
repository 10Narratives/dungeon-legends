#ifndef CORE_ECS_TAG_COMPONENT_H
#define CORE_ECS_TAG_COMPONENT_H

#include "ecs/component-base.h"

namespace core::ecs {

/**
 * @ingroup ecs
 * @brief A tag component used for marking entities without storing additional data.
 *
 * `TagComponent` is a specialized component that serves as a marker or tag for entities.
 * It inherits from `ComponentBase` and does not store any additional data or state.
 * Typically used to denote special properties or behaviors for an entity without adding memory overhead.
 */
struct TagComponent : public ComponentBase {
 public:
  /**
   * @brief Default constructor.
   *
   * Initializes a new instance of `TagComponent`.
   */
  TagComponent() = default;

  /**
   * @brief Destructor.
   *
   * Ensures proper cleanup of `TagComponent` when deleted.
   */
  ~TagComponent() override = default;
};

}  // namespace core::ecs

#endif
