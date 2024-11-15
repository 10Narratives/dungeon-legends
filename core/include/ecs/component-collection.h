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

class ComponentCollection final {
 public:
  ComponentCollection() = default;

  ComponentCollection(const ComponentCollection& other);
  ComponentCollection& operator=(const ComponentCollection& other);

  [[nodiscard]] bool Empty() const noexcept;
  [[nodiscard]] std::size_t Size() const noexcept;
  void Clear();

  template <is_component ComponentType, typename... Args>
  [[maybe_unused]] bool Emplace(Args&&... arguments);

  template <is_component ComponentType>
  [[nodiscard]] component_ptr Extract();

  template <is_component ComponentType>
  [[maybe_unused]] bool Erase();

  template <is_component ComponentType>
  [[nodiscard]] std::weak_ptr<ComponentType> Get();

  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAll() const noexcept;

  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAny() const noexcept;

 private:
  std::unordered_map<std::type_index, component_ptr> inner_components_;
};

template <is_component ComponentType, typename... Args>
[[maybe_unused]] bool ComponentCollection::Emplace(Args&&... arguments) {
    auto new_component_ptr = std::make_shared<ComponentType>(arguments...);
    return inner_components_.try_emplace(typeid(ComponentType), std::move(new_component_ptr)).second;
}

template <is_component ComponentType>
[[nodiscard]] component_ptr ComponentCollection::Extract() {
    component_ptr extracted = nullptr;
    const auto iter = inner_components_.find(typeid(ComponentType));
    if (iter != inner_components_.end()) {
        auto node = inner_components_.extract(iter);
        extracted = node.mapped();
    }
    return extracted;
}

template <is_component ComponentType>
[[maybe_unused]] bool ComponentCollection::Erase() {
    return inner_components_.erase(typeid(ComponentType)) > 0;
}

template <is_component ComponentType>
[[nodiscard]] std::weak_ptr<ComponentType> ComponentCollection::Get() {
    std::shared_ptr<ComponentType> target_component = nullptr;
    const auto iter = inner_components_.find(typeid(ComponentType));
    if (iter != inner_components_.end()) {
        target_component = std::dynamic_pointer_cast<ComponentType>(iter->second);
    }
    return target_component;
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
