
# SDL3

SDL3_Simple est du code C++ issu de l'UE LIFAPCD pour illustré l'usage de SDL3.


# git 

Ce code fait partie du dépôt git de LIFAPCP
https://forge.univ-lyon1.fr/Alexandre.Meyer/L2_ConceptionDevApp



# Installation

Installez VScode et ses extensions, un compileteur, CMake, vcpkg et les lib SDL2...
[Regardez le guide ici](../doc/install.md)

Si vous avez installé SDL2 avec vcpkg, il ne faut pas oublier d'ajouter le chemin vers les .DLL dans votre %PATH%. Et le chemin vers les DLL de debug de vcpkg si vous compiler avec CMake.


# Usage

Lancez le programme comme ceci

* `cd L2_ConceptionDevApp.gituniv/SDL3_Simple`
* `mkdir build`
* `cd build`
* `cmake ..`
* `make`
* `./SDL_Simple`

Vos devriez voir une fenêtre SDL s'ouvrir affichage un pacman.





# Contribution et License
Contributeur :
- Alexandre Meyer
- Nicolas Pronost

Toute idée d'amélioration est bienvenue. Passez par un pull request via la forge. Vous pouvez réutliser ce code comme bon vous semble. Il est là pour ca.

Pour une license plus standard, voyez par exemple
[MIT](https://choosealicense.com/licenses/mit/)
