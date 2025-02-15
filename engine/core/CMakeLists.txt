file(GLOB CORE_HEADER_FILES "include/*.h")
file(GLOB CORE_SOURCE_FILES "source/*.cc")
add_library(engine-core STATIC ${CORE_HEADER_FILES} ${CORE_SOURCE_FILES})
target_include_directories(engine-core PUBLIC include)