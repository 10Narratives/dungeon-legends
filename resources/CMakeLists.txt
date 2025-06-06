add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/bin/$<CONFIG>/resources
    COMMENT "Copying resources to the output directory"
)
add_dependencies(${PROJECT_NAME} copy_resources)
