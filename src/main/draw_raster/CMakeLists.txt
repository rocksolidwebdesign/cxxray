add_executable(draw_raster draw_raster_main.cxx)

target_link_libraries(draw_raster PRIVATE cxxray_core test_fixtures)

add_dependencies(draw_raster copy_test_data)

enable_testing()

add_test(NAME test_draw_raster_test
  COMMAND "${CMAKE_BINARY_DIR}/draw_raster"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
