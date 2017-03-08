cmake_minimum_required(VERSION 3.7.1)
set (CMAKE_CXX_STANDARD 11)
project(boxy)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(include)


file(GLOB SOURCES "src/*.cpp")

add_executable(boxy ${SOURCES})

target_link_libraries(boxy ${SDL2_LIBRARY})
target_link_libraries(boxy ${GLEW_LIBRARIES})
target_link_libraries(boxy ${OPENGL_gl_LIBRARY})
