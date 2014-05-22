cmake_minimum_required(VERSION 2.8)
project(gkom)

#	glfw
add_subdirectory(glfw)


add_executable(gkom main.cpp)
target_link_libraries(gkom glfw)
