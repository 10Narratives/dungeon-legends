include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML
  GIT_TAG        3.0.0
  GIT_SHALLOW    TRUE
)

FetchContent_Declare(
  pugixml
  GIT_REPOSITORY https://github.com/zeux/pugixml
  GIT_TAG v1.15
)


FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.15.3
)

FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(pugixml)
FetchContent_MakeAvailable(sfml)

add_subdirectory(entities)
add_subdirectory(repositories)
add_subdirectory(services)
add_subdirectory(controllers)
add_subdirectory(views)
add_subdirectory(app)
