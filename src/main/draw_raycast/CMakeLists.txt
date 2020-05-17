add_executable(draw_raycast draw_raycast_main.cxx)

target_link_libraries(draw_raycast PRIVATE cxxray_core test_fixtures)

add_dependencies(draw_raycast copy_test_data)

enable_testing()

add_test(NAME test_draw_raycast_test
  COMMAND "${CMAKE_BINARY_DIR}/draw_raycast"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
