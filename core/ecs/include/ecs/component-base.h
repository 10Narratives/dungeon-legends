#ifndef CORE_ECS_COMPONENT_BASE_H
#define CORE_ECS_COMPONENT_BASE_H

namespace core::ecs {

struct ComponentBase {
 public:
  ComponentBase() = default;
  virtual ~ComponentBase() = default;
};

}  // namespace core::ecs

#endif
