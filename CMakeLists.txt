cmake_minimum_required(VERSION 3.26)
project(cpplatformer)

set(CMAKE_CXX_STANDARD 17)
#set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/textures")
find_package(raylib CONFIG REQUIRED VERSION 5.0.0)
add_executable(cpplatformer main.cpp)
target_link_libraries(cpplatformer PRIVATE raylib)
# Copy your textures directory to the build directory after the build
add_custom_command(TARGET cpplatformer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/textures $<TARGET_FILE_DIR:cpplatformer>/assets/textures)
add_custom_command(TARGET cpplatformer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/sounds $<TARGET_FILE_DIR:cpplatformer>/assets/sounds)
