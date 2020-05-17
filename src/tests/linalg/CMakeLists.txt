add_executable(test_linalg linalg.cxx)

target_link_libraries(test_linalg PRIVATE cxxray_core)

enable_testing()

add_test(NAME test_linalg_test
  COMMAND "${CMAKE_BINARY_DIR}/test_linalg"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
