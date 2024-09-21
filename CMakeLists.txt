cmake_minimum_required(VERSION 3.22)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 6)
set(VERSION_PATCH 0)

project(lorem_invader VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} LANGUAGES CXX)

# Enable CMake to generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CPP_STANDARD 17)

# Our project
add_executable(${PROJECT_NAME} src/main.cc)
include_directories(lib/includes)
add_subdirectory(lib/raylib)
add_subdirectory(src)

add_definitions(-DVERSION_MAJOR=${VERSION_MAJOR})
add_definitions(-DVERSION_MINOR=${VERSION_MINOR})
add_definitions(-DVERSION_PATCH=${VERSION_PATCH})

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
        DEPENDS ${PROJECT_NAME})

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

# Web Configurations
if (EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/resources@resources")
    target_link_options(${PROJECT_NAME} PUBLIC "-sUSE_GLFW=3")
endif ()