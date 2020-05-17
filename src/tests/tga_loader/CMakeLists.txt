add_executable(test_tga_loader tga_loader.cxx)

target_link_libraries(test_tga_loader PRIVATE cxxray_core)

add_dependencies(test_tga_loader copy_test_data)

enable_testing()

add_test(NAME test_tga_loader_test
  COMMAND "${CMAKE_BINARY_DIR}/test_tga_loader"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
