enable_testing()

add_custom_target(copy_test_data
  COMMAND "${CMAKE_COMMAND}" -E copy_directory
    "${CMAKE_SOURCE_DIR}/data"
    "${CMAKE_BINARY_DIR}/data"
)

add_subdirectory("core")
add_subdirectory("main")
add_subdirectory("tests")
