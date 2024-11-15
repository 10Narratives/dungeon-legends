#ifndef CORE_ECS_COMPONENT_BASE_H
#define CORE_ECS_COMPONENT_BASE_H

#include <memory>

namespace core::ecs {

struct ComponentBase {
 public:
  ComponentBase() = default;
  virtual ~ComponentBase() = default;
};

using component_ptr = std::shared_ptr<ComponentBase>;

}  // namespace core::ecs

#endif
