# Usage :
# 0. Sous Windows, ne pas oublier de mettre dans la variable d'environnement PATH le chemin vers le dossier contenant gcc et g++ (ex. C:\Program Files (x86)\CodeBlocks\MinGW\bin)
# 1. Mettre ce fichier dans le dossier racine du projet
# 2. Créer et se placer dans le répertoire build
# 3. Lancer la configuration et la génération du projet : cmake -G "generateur" .. (où "generateur" est "Unix Makefiles", "MinGW Makefiles", ou "Visual Studio XX 20XX" etc.)
# 4. Compiler le projet : cmake --build . (où appel à make ou à mingw32-make.exe ou bien compilation sous CodeBlock, Visual Studio etc.)
# 5. Lancer les exécutables (pacman_sdl ou pacman_txt)

cmake_minimum_required(VERSION 3.22)

# Le projet
project(Pacman)

# Les dossiers
set(SRC_CORE_DIR ./src/core)
set(SRC_SDL2_DIR ./src/sdl2)
set(SRC_TXT_DIR ./src/txt)

# Les sources
set(SRC_CORE ${SRC_CORE_DIR}/Fantome.cpp ${SRC_CORE_DIR}/Jeu.cpp ${SRC_CORE_DIR}/Pacman.cpp ${SRC_CORE_DIR}/Terrain.cpp)
set(HEADER_CORE ${SRC_CORE_DIR}/Fantome.h ${SRC_CORE_DIR}/Jeu.h ${SRC_CORE_DIR}/Pacman.h ${SRC_CORE_DIR}/Terrain.h)
set(SRC_SDL2 ${SRC_SDL2_DIR}/main_sdl.cpp ${SRC_SDL2_DIR}/SDLJeu.cpp ${SRC_SDL2_DIR}/SDLJeu.h ${SRC_SDL2_DIR}/SDLSprite.h ${SRC_SDL2_DIR}/SDLSprite.cpp)
set(SRC_TXT ${SRC_TXT_DIR}/main_txt.cpp ${SRC_TXT_DIR}/txtJeu.cpp ${SRC_TXT_DIR}/winTxt.h ${SRC_TXT_DIR}/winTxt.cpp)

# Les libs (SDL2) 
if (WIN32)
	# lib SDL2
	set(SDL2_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2-2.0.12/x86_64-w64-mingw32)
	set(SDL2_INCLUDE_DIR ${SDL2_DIR}/include/SDL2)
	set(SDL2_LIBRARY ${SDL2_DIR}/lib)
	
	# lib SDL2 image
	set(SDL2_IMAGE_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2_image-2.0.5/x86_64-w64-mingw32)
	set(SDL2_IMAGE_INCLUDE_DIR ${SDL2_IMAGE_DIR}/include/SDL2)
	set(SDL2_IMAGE_LIBRARY ${SDL2_IMAGE_DIR}/lib)
	
	# lib SDL2 ttf
	set(SDL2_TTF_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2_ttf-2.0.15/x86_64-w64-mingw32)
	set(SDL2_TTF_INCLUDE_DIR ${SDL2_TTF_DIR}/include/SDL2)
	set(SDL2_TTF_LIBRARY ${SDL2_TTF_DIR}/lib)	
		
	# lib SDL2 mixer
	set(SDL2_MIXER_DIR ${PROJECT_SOURCE_DIR}/extern/SDL2_mingw-cb20/SDL2_mixer-2.0.4/x86_64-w64-mingw32)
	set(SDL2_MIXER_INCLUDE_DIR ${SDL2_MIXER_DIR}/include/SDL2)
	set(SDL2_MIXER_LIBRARY ${SDL2_MIXER_DIR}/lib)
endif (WIN32)
if (UNIX)
	# lib SDL2
	set(SDL2_INCLUDE_DIR /usr/include/SDL2)
	set(SDL2_LIBRARY /usr/lib)
	
	# lib SDL2 image
	set(SDL2_IMAGE_INCLUDE_DIR ${SDL2_INCLUDE_DIR})
	set(SDL2_IMAGE_LIBRARY ${SDL2_LIBRARY})
	
	# lib SDL2 ttf
	set(SDL2_TTF_INCLUDE_DIR ${SDL2_INCLUDE_DIR})
	set(SDL2_TTF_LIBRARY ${SDL2_LIBRARY})
	
	# lib SDL2 mixer
	set(SDL2_MIXER_INCLUDE_DIR ${SDL2_INCLUDE_DIR})
	set(SDL2_MIXER_LIBRARY ${SDL2_LIBRARY})
endif (UNIX)

# Les executables
add_executable(pacman_sdl ${SRC_CORE} ${HEADER_CORE} ${SRC_SDL2})
add_executable(pacman_txt ${SRC_CORE} ${HEADER_CORE} ${SRC_TXT})

# Include compilation
target_include_directories(pacman_sdl PUBLIC ${SRC_CORE_DIR} ${SRC_SDL2_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
target_include_directories(pacman_txt PUBLIC ${SRC_CORE_DIR} ${SRC_TXT_DIR})

# Les options de compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb")

# Include édition des liens
target_link_directories(pacman_sdl PUBLIC ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})

# Librairies édition des liens
if (WIN32)
	target_link_libraries(pacman_sdl mingw32 SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)
endif (WIN32)
if (UNIX)
	target_link_libraries(pacman_sdl SDL2 SDL2_image SDL2_ttf SDL2_mixer GL)
endif (UNIX)

# Copie les dll de SDL si Win32
if (WIN32)
	file(COPY ${SDL2_DIR}/bin/SDL2.dll ${SDL2_IMAGE_DIR}/bin/libjpeg-9.dll ${SDL2_IMAGE_DIR}/bin/libpng16-16.dll ${SDL2_IMAGE_DIR}/bin/libtiff-5.dll ${SDL2_IMAGE_DIR}/bin/libwebp-7.dll ${SDL2_IMAGE_DIR}/bin/SDL2_image.dll ${SDL2_IMAGE_DIR}/bin/zlib1.dll ${SDL2_TTF_DIR}/bin/libfreetype-6.dll ${SDL2_TTF_DIR}/bin/SDL2_ttf.dll ${SDL2_MIXER_DIR}/bin/libFLAC-8.dll ${SDL2_MIXER_DIR}/bin/libmodplug-1.dll ${SDL2_MIXER_DIR}/bin/libmpg123-0.dll ${SDL2_MIXER_DIR}/bin/libogg-0.dll ${SDL2_MIXER_DIR}/bin/libopus-0.dll ${SDL2_MIXER_DIR}/bin/libopusfile-0.dll ${SDL2_MIXER_DIR}/bin/libvorbis-0.dll ${SDL2_MIXER_DIR}/bin/libvorbisfile-3.dll ${SDL2_MIXER_DIR}/bin/SDL2_mixer.dll DESTINATION ${CMAKE_BINARY_DIR})
endif (WIN32)
