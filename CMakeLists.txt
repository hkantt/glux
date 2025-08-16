cmake_minimum_required(VERSION 3.15)
project(glux VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/external/glad)
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/external/glfw)
set(OPENAL_DIR ${CMAKE_SOURCE_DIR}/external/openal)

file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB IMGUI_SOURCES ${IMGUI_DIR}/src/*.cpp)

add_library(glux MODULE
    ${SRC_FILES}
    ${IMGUI_SOURCES}
    ${GLAD_DIR}/src/gl.c
)

set_target_properties(glux PROPERTIES
    PREFIX ""
    SUFFIX ".pyd"
)

target_include_directories(glux PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${IMGUI_DIR}/include
    ${GLAD_DIR}/include
    ${GLFW_DIR}/include
    ${OPENAL_DIR}/include
    ${Python3_INCLUDE_DIRS}
)

target_link_directories(glux PRIVATE ${GLFW_DIR}/lib ${OPENAL_DIR}/lib)

target_compile_definitions(glux PRIVATE AL_LIBTYPE_STATIC)

# Libraries
target_link_libraries(glux PRIVATE
    winmm
    avrt
    glfw3
    OpenAL32
    opengl32
    user32 
    gdi32
    shell32
    pybind11::module
)