cmake_minimum_required(VERSION 3.22)
project(opengl_course)

set(CMAKE_CXX_STANDARD 17)
add_executable(opengl_course main.cpp src/glad.c)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(opengl_course  ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)

# Copies lib directory files to build directory
add_custom_command(TARGET opengl_course POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${PROJECT_SOURCE_DIR}/lib"
                   $<TARGET_FILE_DIR:opengl_course>)