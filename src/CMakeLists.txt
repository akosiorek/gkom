cmake_minimum_required(VERSION 2.8)
project(gkom)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake_modules)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenCV COMPONENTS core highgui REQUIRED)

#	glfw
set(BUILD_SHARED_LIBS ON)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS  OFF)
set(GLFW_BUILD_DOCS OFF) 
set(GLFW_INSTALL OFF)
add_subdirectory(glfw)

include_directories( 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIRS}  
    ${GLUT_INCLUDE_DIRS} 
    glfw/include
    ${GLM_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
) 

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(gkom ${SOURCES}) 

target_link_libraries(gkom 
        glfw
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        ${GLEW_LIBRARIES} 
        ${OpenCV_LIBS}
) 
