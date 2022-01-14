cmake_minimum_required(VERSION 3.16)

project(raytracer)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(raytracer ${SOURCES})

include_directories(include)

set_target_properties(raytracer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

target_link_libraries(raytracer ${CMAKE_CURRENT_SOURCE_DIR}/lib/libyaml-cpp.dll.a)

