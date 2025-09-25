cmake_minimum_required(VERSION 3.14)

project(Kaleidoscope VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(src)
add_subdirectory(tests)

install(TARGETS kaleidoscope DESTINATION bin)
