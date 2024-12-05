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

  [[nodiscard]] std::size_t Size() const noexcept;

  [[nodiscard]] bool Empty() const noexcept;

  void Clear();

  template <is_component ComponentType, typename... Args>
  [[maybe_unused]] bool Emplace(Args&&... arguments);

  template <is_component ComponentType>
  [[nodiscard]] component_ptr Extract();

  template <is_component ComponentType>
  [[maybe_unused]] bool Erase();

  template <is_component ComponentType>
  std::weak_ptr<ComponentType> Get();

  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAll() const noexcept;

  template <is_component... ComponentTypes>
  [[nodiscard]] bool HasAny() const noexcept;

 private:
  std::unordered_map<std::type_index, component_ptr> inner_components_;
};

template <is_component ComponentType, typename... Args>
[[maybe_unused]] bool ComponentCollection::Emplace(Args&&... arguments) {
  auto new_component = std::make_shared<ComponentType>(std::forward<Args>(arguments)...);
  return inner_components_.try_emplace(typeid(ComponentType), std::move(new_component)).second;
}

template <is_component ComponentType>
component_ptr ComponentCollection::Extract() {
  std::shared_ptr<ComponentBase> extracted_component{nullptr};
  if (inner_components_.contains(typeid(ComponentType))) {
    auto node = inner_components_.extract(typeid(ComponentType));
    extracted_component = std::move(node.mapped());
  }
  return extracted_component;
}

template <is_component ComponentType>
bool ComponentCollection::Erase() {
  return inner_components_.erase(typeid(ComponentType)) > 0;
}

template <is_component ComponentType>
std::weak_ptr<ComponentType> ComponentCollection::Get() {
  std::shared_ptr<ComponentType> found_component{nullptr};
  auto iter = inner_components_.find(typeid(ComponentType));
  if (iter != inner_components_.end()) {
    found_component = std::dynamic_pointer_cast<ComponentType>(iter->second);
  }
  return found_component;
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
