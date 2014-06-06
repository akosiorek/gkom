cmake_minimum_required(VERSION 2.8)
project(gkom)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake_modules)
set(BUILD_SHARED_LIBS ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenCV COMPONENTS core highgui REQUIRED)

#	glfw
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS  OFF)
set(GLFW_BUILD_DOCS OFF) 
set(GLFW_INSTALL OFF)
add_subdirectory(glfw)
 
set(FOLDERS 
        Technique  
        Mesh 
        Graphics 
        Generator  
) 

#   Get absolute source folders paths
set(SOURCE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
foreach(folder ${FOLDERS})
    set(SOURCE_DIRS ${SOURCE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/${folder})
endforeach()

#   Get source files
foreach(source_dir ${SOURCE_DIRS})
    file(GLOB files ${source_dir}/*.cpp)
    list(APPEND SOURCES ${files})
endforeach()

include_directories( 
    ${SOURCE_DIRS}
    ${OPENGL_INCLUDE_DIRS}   
    ${GLUT_INCLUDE_DIRS} 
    glfw/include 
    ${GLM_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
) 


add_executable(gkom ${SOURCES}) 

target_link_libraries(gkom 
        glfw
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        ${GLEW_LIBRARIES} 
        ${OpenCV_LIBS}
) 
