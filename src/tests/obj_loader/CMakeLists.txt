add_executable(test_obj_loader obj_loader.cxx)

target_link_libraries(test_obj_loader PRIVATE cxxray_core)

add_dependencies(test_obj_loader copy_test_data)

enable_testing()

add_test(NAME test_obj_loader_test
  COMMAND "${CMAKE_BINARY_DIR}/test_obj_loader"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
