#ifndef CORE_ECS_TYPE_TRAITS_H
#define CORE_ECS_TYPE_TRAITS_H

#include <concepts>

#include "component-base.h"
#include "ecs/tag-component.h"

namespace core::ecs {

/**
 * @defgroup ecs ECS
 * @brief Entity-Component-System (ECS) module.
 */

/**
 * @ingroup ecs
 * @brief Concept to verify if a type is a component.
 *
 * The `is_component` concept checks if a type is derived from `ComponentBase`.
 * It is used to constrain template parameters, ensuring that only valid component types
 * are used in the ECS system.
 *
 * @tparam T The type to check.
 * @concept is_component
 */
template <typename T>
concept is_component = std::derived_from<T, ComponentBase>;

/**
 * @ingroup ecs
 * @brief Concept to verify if a type is a tag component.
 *
 * The `is_tag_component` concept checks if a type is derived from `TagComponent`.
 * It is used to identify components that act as markers or tags without additional data.
 *
 * @tparam T The type to check.
 * @concept is_tag_component
 */
template <typename T>
concept is_tag_component = std::derived_from<T, TagComponent>;

}  // namespace core::ecs

#endif
