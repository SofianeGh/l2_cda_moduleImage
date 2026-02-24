cmake_minimum_required(VERSION 3.16)

set(CMAKE_DEBUG_POSTFIX "")

project(SDL_Simple)
set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    message("Configuring for Windows")
    # Adapter le chemin vcpkg si nécessaire
    set(CMAKE_PREFIX_PATH "C:/dev/vcpkg/installed/x64-windows/")
    set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
elseif(APPLE)
    message("Configuring for macOS")
else()
    message("Configuring for Linux")
endif()

# ===============================
# Recherche SDL3
# ===============================

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_mixer CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

message("SDL3_FOUND = ${SDL3_FOUND}")
message("SDL3_image_FOUND = ${SDL3_image_FOUND}")
message("SDL3_mixer_FOUND = ${SDL3_mixer_FOUND}")
message("SDL3_ttf_FOUND = ${SDL3_ttf_FOUND}")

message("Type de build: ${CMAKE_BUILD_TYPE}")

set(CMAKE_VERBOSE_MAKEFILE ON)

# ===============================
# Executable
# ===============================

add_executable(SDL_Simple src/SDL_Simple.cpp)

# ===============================
# Link libraries (modern CMake)
# ===============================

target_link_libraries(SDL_Simple PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
)

# ===============================
# Installation
# ===============================

get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)
message("Chemin vers CMakeLists.txt : ${PROJECT_ROOT}")

install(TARGETS SDL_Simple DESTINATION "${PROJECT_ROOT}/bin")