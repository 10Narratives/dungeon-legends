#ifndef CORE_ECS_TYPE_TRAITS_H
#define CORE_ECS_TYPE_TRAITS_H

#include <concepts>
#include <type_traits>

#include "component-base.h"

namespace core::ecs {

/**
 * @brief Concept that defines a valid component type for the Entity-Component-System (ECS) framework.
 *
 * This concept ensures that a type `T` qualifies as a valid component in the ECS framework by verifying
 * that the type satisfies the following conditions:
 *
 * 1. The type must be derived from the `ComponentBase` class.
 * 2. The type must be copy-constructible, allowing components to be copied.
 * 3. The type must be copy-assignable, allowing components to be assigned.
 * 4. The type must be move-constructible, enabling efficient movement of components.
 * 5. The type must be move-assignable, ensuring that components can be moved between containers.
 *
 * These checks ensure that the type `T` can be used as a component in the ECS system, which typically requires
 * supporting both copy and move operations, along with inheritance from a common base class (`ComponentBase`).
 *
 * @tparam T The type to be checked as a valid component.
 *
 * @note This concept is used to constrain template parameters in ECS systems, ensuring that only valid components
 *       can be stored, moved, and copied within component collections.
 *
 * @example
 * ```cpp
 * struct Position : public ComponentBase { int x, y; };
 * static_assert(is_component<Position>);  // This will compile because Position is derived from ComponentBase,
 *                                         // and supports copy and move operations.
 *
 * struct NonCopyableComponent : public ComponentBase {
 *     NonCopyableComponent() = default;
 *     NonCopyableComponent(const NonCopyableComponent&) = delete;
 *     NonCopyableComponent& operator=(const NonCopyableComponent&) = delete;
 * };
 * static_assert(!is_component<NonCopyableComponent>);  // This will fail because NonCopyableComponent is not
 *                                                     // copy-constructible or copy-assignable.
 * ```
 */
template <typename T>
concept is_component = std::derived_from<T, ComponentBase> && std::is_copy_constructible_v<T> &&
                       std::is_copy_assignable_v<T> && std::is_move_constructible_v<T> && std::is_move_assignable_v<T>;

}  // namespace core::ecs

#endif
