cmake_minimum_required(VERSION 3.11)
cmake_policy(SET CMP0072 NEW)

project(MODEL_WOLF)

# Set the folder where the executable will be created
set(OUTPUT_BIN_FOLDER ${CMAKE_SOURCE_DIR}/bin)

# Configure assets header file
# tips found here : https://shot511.github.io/2018-05-29-how-to-setup-opengl-project-with-cmake/
include_directories(${CMAKE_BINARY_DIR}/src)

# Librairies

# ---Add GL---
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
set(ALL_LIBRARIES ${OPENGL_LIBRARIES})

# ---Add GLFW---
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/glfw)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glfw)

# ---Add glad---
add_library(glad third_party/glad/src/glad.c)
include_directories(third_party/glad/include)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glad)

include_directories(.)

add_subdirectory(src)
# file(GLOB TD_DIRECTORIES "TD*")

# foreach(TD ${TD_DIRECTORIES})
#     add_subdirectory(${TD})
# 	get_filename_component(DIRN ${TD} NAME)
#     add_custom_target(${DIRN} COMMAND cd ${CMAKE_CURRENT_BINARY_DIR}/${DIRN} COMMAND make
#                 WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${DIRN})
# endforeach()
