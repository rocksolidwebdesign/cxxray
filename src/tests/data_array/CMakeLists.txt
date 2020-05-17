add_executable(test_data_array data_array.cxx)

target_link_libraries(test_data_array PUBLIC cxxray_core)

add_dependencies(test_data_array copy_test_data)

add_test(NAME test_data_array_test
  COMMAND "${CMAKE_BINARY_DIR}/test_data_array"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
