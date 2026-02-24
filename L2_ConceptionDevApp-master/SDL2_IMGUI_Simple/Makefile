

all: bin/SDL_IMGUI_Simple bin/demo


bin/SDL_IMGUI_Simple: src/SDL_IMGUI_Simple.cpp
	mkdir -p bin; g++ -o bin/SDL_IMGUI_Simple src/SDL_IMGUI_Simple.cpp src/imgui/*.cpp -Isrc/imgui -I/usr/include/SDL2 -lSDL2 -lSDL2_image -lSDL2_ttf -ldl -lGL -lGLEW

bin/demo: src/demo.cpp
	mkdir -p bin ; g++ -o bin/demo src/demo.cpp src/imgui/*.cpp -Isrc/imgui -I/usr/include/SDL2 -lSDL2 -lSDL2_image -lSDL2_ttf -ldl -lGL

clean:
	rm -rf bin/*
