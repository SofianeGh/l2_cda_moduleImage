# LIFAPCD Conception et Développement d'Applications

Dépôt servant d'illustration, de code, d'exemples pour le cours "Conception et Développement d'Applications en C++" de la L2 Informatique de l'Université Lyon 1.

De nombreuses explications sur les outils sont dans le [répertoire doc](./doc/) et [sur la page du cours](http://licence-info.univ-lyon1.fr/LIFAPCD).



## Organisation des fichiers/répertoires

- **doc**" : de nombreuses explications sur tous les outils à connaître. Installation (linux, windows, macos), git, doxygen, les IDE, Makefile, CMake, des librairies (SDL2, imgui, ...), etc.

- **exemples_cours**  : quelques exemples de code simple qui sont décrits durant les CM

- **SDL2_Simple**    : un code minimaliste qui ouvre une fenêtre SDL2. Utile pour le module Image à rendre, pour la question affichage de l'image. Également utile pour tout projet à commencer.

- **SDL2_IMGUI_Simple** : un code minimaliste qui ouvre une fenêtre SDL2 avec imgui comme ihm/widgets. Utile pour tout projet qui a besoin d'une IHM sympa (sans passer à Qt).

- **TD_moduleImage**  : les scripts qui servent à évaluer le module Image. Le script en python teste l'archive et donne toutes les remarques. Voir la page de LIFAPCD, rubrique : rendu du module Image (TD outils)

- **TD_Valgrind**     : du code que vous devez inspecter avec Valgrind durant le TD Outils

- **Pacman**          : le code "fil rouge" du cours. Il illustre tous les principes : code séparé (core != ihm), git, valgrind, SDL, qt, etc.

- **.gitignore**      : pour exclure des fichiers des ajouts automatiques de git. Ajoutez également un .gitignore dans votre projet !

- **README.md**       : ce readme
