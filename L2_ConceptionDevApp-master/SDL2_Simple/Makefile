


# Edition de lien (g++ assemble les .o et les lib pour faire un éxécutable)
# -l indique une librairie (par exempel g++ va chercher un fichier se nommant libTruc.so quand on met -lTruc). Pas d'espace après le -l
# -L pour indiquer un chemin de répertoire contenant des librairies (pas d'espace après le -L)
src/SDL_SDL_Simple: obj/SDL_Simple.o
	mkdir -p bin ; g++ -o bin/SDL_Simple obj/SDL_Simple.o -lSDL2 -lSDL2_ttf -lSDL2_image


# compilation (traduit le fichier .cpp en du code objet .o, ce n'est pas encore un exécutable) 
# l'option -c indique à g++ la compilation
# -I pour donner un chemin vers un répertoire qui contient les .h. Pas d'espace après le -I
# Par exemple -ISDL2 fera que g++ va chercher dans tous les répertoires standards + ces mêmes répertoires complétés par "/SDL2"
obj/SDL_Simple.o: src/SDL_Simple.cpp
	mkdir -p obj ; g++ -o obj/SDL_Simple.o src/SDL_Simple.cpp -c -ISDL2


sdl.supp: SDL_Simple
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --error-limit=no --gen-suppressions=all --log-file=supdata.log ./bin/SDL_Simple
	./valgrind_sup_error.sh supdata.log > sdl.supp


clean:
	rm -rf bin/* obj/* obj bin
