#ifndef CORE_ECS_TYPE_TRAITS_H
#define CORE_ECS_TYPE_TRAITS_H

#include <concepts>
#include "component-base.h"

namespace core::ecs {

template<typename T>
concept is_component = std::derived_from<T, ComponentBase>;

}

#endif
