#ifndef CORE_ECS_ENTITY_H
#define CORE_ECS_ENTITY_H

#include <cstddef>
#include <string>
#include <unordered_set>

#include "ecs/component-collection.h"
namespace core::ecs {

class EntityID {
 public:
  EntityID();

  [[nodiscard]] std::string GetInnerData() const noexcept;

  [[nodiscard]] static EntityID GetRootID() noexcept;

  [[nodiscard]] bool operator<=>(const EntityID& other) const noexcept = default;

  struct Hash final {
   public:
    [[nodiscard]] std::size_t operator()(const EntityID& id) const noexcept;
  };

 private:
  std::string inner_data_;
};

using EntityIDSet = std::unordered_set<EntityID, EntityID::Hash>;

struct Entity final {
 public:
  Entity() = default;

  EntityID parent_id_{EntityID::GetRootID()};
  EntityIDSet children_ids_;
  ComponentCollection data_;
};

}  // namespace core::ecs

#endif
