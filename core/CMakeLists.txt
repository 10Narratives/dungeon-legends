file(GLOB CORE_SOURCE_FILES "source/*.cc")
file(GLOB CORE_HEADER_FIELS "include/*.h")
add_library(core STATIC ${CORE_SOURCE_FILES} ${CORE_HEADER_FIELS})
target_include_directories(core PUBLIC include)
