add_executable(test_gamma gamma.cxx)

target_link_libraries(test_gamma PRIVATE cxxray_core)

add_dependencies(test_gamma copy_test_data)

enable_testing()

add_test(NAME test_gamma_test
  COMMAND "${CMAKE_BINARY_DIR}/test_gamma"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
