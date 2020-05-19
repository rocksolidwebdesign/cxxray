cmake_minimum_required(VERSION 3.14)

project(CxxRay)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MORE_WARNINGS "Show lots and lots of warnings, LOTS I TELL YOU!." ON)

if(MORE_WARNINGS)
  if(MSVC)
    add_compile_options("/W4")
  else()
    add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-Wconversion")
  endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_subdirectory("src")
