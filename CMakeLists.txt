cmake_minimum_required(VERSION 3.27)
project(Simulator VERSION 0.1.0 LANGUAGES C CXX)

if(NOT WIN32)
# message("-fsanitize=address is enabled!")
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
endif(NOT WIN32)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works (in creating the compile_commands.json file)

include(CTest)
enable_testing()

find_package(glfw3 REQUIRED)
find_package(box2d REQUIRED)
find_package(spdlog REQUIRED)
find_package(imgui REQUIRED)
find_package(glad REQUIRED)

set(
    all_src
    main.cpp
)

add_executable(Simulator ${all_src})

target_link_libraries(
    ${PROJECT_NAME}
    glfw
    ${OpenGL_LIBRARIES}
    spdlog::spdlog
    box2d::box2d
    imgui::imgui
    glad::glad
)

# Before we copy compile_commands.json to .vscode
# Making sure we should make sure if that dir already exists in the root of the projects directory
set(VSCODE_DIR "${CMAKE_CURRENT_LIST_DIR}/.vscode")
if(NOT EXISTS ${VSCODE_DIR})
    file(MAKE_DIRECTORY ${VSCODE_DIR})
endif()

# Copy to source directory
add_custom_target(
    copy-compile-commands ALL
    DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json
)

# Creating a customize command specific for copying the compile_commands.json to users .vscode directory
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_LIST_DIR}/.vscode/compile_commands.json
    DEPENDS
    # Unlike "proper" targets like executables and libraries, 
    # custom command / target pairs will not set up source
    # file dependencies, so we need to list file explicitly here
    generate-compile-commands
    ${CMAKE_BINARY_DIR}/compile_commands.json
)

# Generate the compilation commands. Necessary so cmake knows where it came
# from and if for some reason you delete it.
add_custom_target(generate-compile-commands
    DEPENDS
        ${CMAKE_BINARY_DIR}/compile_commands.json
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
