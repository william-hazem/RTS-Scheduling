cmake_minimum_required(VERSION 3.25.0)
project(SCHEDULING CXX)

set(json-c_DIR "${CMAKE_SOURCE_DIR}/lib/json-c/lib/cmake/json-c")
find_package(json-c REQUIRED)



include_directories("${CMAKE_SOURCE_DIR}/lib/json-c/include}")

add_executable(main main.cpp)
target_link_libraries(main json-c::json-c-static)