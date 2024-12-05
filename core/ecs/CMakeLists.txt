file(GLOB CORE_ECS_INCLUDE_FILES "include/*.hh")
file(GLOB CORE_ECS_SOURCE_FILES "source/*.cc")
add_library(ecs ${CORE_ECS_INCLUDE_FILES} ${CORE_ECS_SOURCE_FILES})
target_include_directories(ecs PUBLIC include)
