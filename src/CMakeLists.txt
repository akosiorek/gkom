cmake_minimum_required(VERSION 2.8)
project(gkom)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake_modules)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

#	glfw
set(BUILD_SHARED_LIBS ON)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS  OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(glfw)

include_directories( 
    ${OPENGL_INCLUDE_DIRS}  
    ${GLUT_INCLUDE_DIRS} 
    glfw/include
    #${glfw_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
) 

add_executable(gkom 
        main.cpp
        Mesh.cpp
        Node.cpp
        PerspectiveCamera.cpp
        RendererOGL.cpp
        Texture.cpp
 )

target_link_libraries(gkom 
        glfw
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        ${GLEW_LIBRARIES} 
)
