if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
	message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the SDL template source code and run \"cmake -S '${CMAKE_SOURCE_DIR}' -B .\" from there")
endif()

cmake_minimum_required(VERSION 3.0.0...3.5)
project(SDL2_template C)

set(EXE program)
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(CFG_DIR "${CMAKE_BINARY_DIR}/cfg")

set(DATA_DIR "${CMAKE_SOURCE_DIR}/data/")
set(SAVE_DIR "${CMAKE_SOURCE_DIR}/save/")

add_executable("${EXE}"
    "${SRC_DIR}/main.c"
)

target_include_directories("${EXE}" PRIVATE
    "${SRC_DIR}"
    "${CFG_DIR}"
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_net REQUIRED)
target_link_libraries("${EXE}" PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
    SDL2_net::SDL2_net
)

configure_file("${SRC_DIR}/config.h.in" "${CFG_DIR}/config.h")
target_sources("${EXE}" PRIVATE "${CFG_DIR}/config.h")

# vi: set ts=4 sw=4 expandtab:
