file(GLOB ENGINE_CORE_HEADER_FILES "include/*.hpp")
file(GLOB ENGINE_CORE_SOURCE_FILES "source/*.cpp")
add_library(engine-core STATIC ${ENGINE_CORE_HEADER_FILES} ${ENGINE_CORE_SOURCE_FILES})
target_include_directories(engine-core PUBLIC include)