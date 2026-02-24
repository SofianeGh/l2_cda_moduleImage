# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

set(CMAKE_DEBUG_POSTFIX "")

# Nom du projet
project(SDL_IMGUI_Simple)
set(CMAKE_CXX_STANDARD 17)


if(WIN32)
    message("Configuring for Windows")
    # TODO: remplacer c:/dev/vcpkg par "<chemin_vers_vcpkg>/
    SET(CMAKE_PREFIX_PATH "C:/dev/vcpkg/installed/x64-windows/")
    set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
elseif(UNIX)
    if(APPLE)
        message("Configuring for macOS")
        #set(CMAKE_PREFIX_PATH "/usr/share/cmake-3.21/Modules/")
    else()
        message("Configuring for Linux")
        #set(CMAKE_PREFIX_PATH "/usr/share/cmake-3.21/Modules/")
    endif()
endif()


# Recherche des bibliothèques SDL2, SDL2_image, SDL2_mixer et SDL2_ttf
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(OpenGL REQUIRED)


# Affichage des informations sur les bibliothèques trouvées
message( "SDL2_image_FOUND=${SDL2_image_FOUND}")
message( "SDL2_mixer_FOUND=${SDL2_mixer_FOUND}")
message( "SDL2_ttf_FOUND=${SDL2_ttf_FOUND}")
message( "OpenGL_FOUND=${OPENGL_FOUND}")

message( "SDL2=${SDL2_LIBRARIES}")
message( "SDL2_image=${SDL2_IMAGE_LIBRARIES}")
message( "SDL2_mixer=${SDL2_MIXER_LIBRARIES}")
message( "SDL2_ttf=${SDL2_TTF_LIBRARIES}")
message( "OPENGL_LIBRARIES = ${OPENGL_LIBRARIES}")

message( "SDL2 include=${SDL2_INCLUDE_DIRS}")
message( "SDL2_image include=${SDL2_IMAGE_INCLUDE_DIRS}")
message( "SDL2_mixer include=${SDL2_MIXER_INCLUDE_DIRS}")
message( "SDL2_ttf include=${SDL2_TTF_INCLUDE_DIRS}")
message( "OpenGL include=${OPENGL_INCLUDE_DIRS}")

message( "SDL_CMAKE_DEBUG_POSTFIX=${SDL_CMAKE_DEBUG_POSTFIX}")
message("Type de build: ${CMAKE_BUILD_TYPE}")




set( CMAKE_VERBOSE_MAKEFILE ON)

# Configuration de l'exécutable
add_executable(SDL_IMGUI_Simple 
                    src/SDL_IMGUI_Simple.cpp
                    src/imgui/imgui.cpp  
                    src/imgui/imgui_demo.cpp  
                    src/imgui/imgui_draw.cpp  
                    src/imgui/imgui_impl_opengl3.cpp  
                    src/imgui/imgui_impl_sdl.cpp  
                    src/imgui/imgui_tables.cpp  
                    src/imgui/imgui_widgets.cpp
    )


# Inclusion des en-têtes des bibliothèques
target_include_directories(SDL_IMGUI_Simple PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    src/imgui
)

# Liaison avec les bibliothèques
if(WIN32)
    target_link_libraries(SDL_IMGUI_Simple PRIVATE 
                SDL2::SDL2main
                SDL2::SDL2
                SDL2_ttf::SDL2_ttf
                SDL2_image::SDL2_image
                SDL2_mixer::SDL2_mixer;
                ${OPENGL_LIBRARIES}
                #"Shlwapi.lib"
    )
else()      # APPLE and LINUX     
    target_link_libraries(SDL_IMGUI_Simple PRIVATE 
                SDL2
                SDL2_ttf
                SDL2_image
                SDL2_mixer
                ${OPENGL_LIBRARIES}
    )
endif()






# Spécifier les fichiers à installer
## chemin vers le CMakeLists.txt en utilisant CMAKE_CURRENT_SOURCE_DIR
get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)
message("Chemin vers CMakeLists.txt : ${PROJECT_ROOT}")
install(TARGETS SDL_IMGUI_Simple DESTINATION "${PROJECT_ROOT}/bin")
