file(GLOB APP_HEADER_FILES "include/*.hpp")
file(GLOB APP_SOURCE_FILES "source/*.cpp")

add_library(app STATIC
    ${APP_HEADER_FILES}
    ${APP_SOURCE_FILES}
)
target_link_libraries(app PUBLIC
    SFML::Graphics
    SFML::System
    SFML::Window
    pugixml::pugixml
    spdlog::spdlog
)

target_include_directories(app PUBLIC include)
