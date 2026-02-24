# Makefile

Un Makefile est un fichier utilisé dans le développement de logiciels pour automatiser le processus de compilation et de construction d'un programme à partir de son code source. Il est couramment utilisé dans les projets basés sur des langages de programmation tels que C, C++, Fortran, et d'autres. L'objectif principal d'un Makefile est de spécifier les dépendances entre différents fichiers source et de définir les règles pour les compiler en un programme exécutable.

L'utilisation d'un Makefile simplifie le processus de gestion des projets complexes en automatisant les tâches répétitives telles que la compilation, la génération de fichiers intermédiaires, la gestion des dépendances, et l'installation du logiciel. En général, un Makefile suit une syntaxe spécifique qui permet au programme Make de comprendre comment construire le projet.


## Cibles (Targets)

Les cibles représentent les différents résultats que le Makefile peut produire. Par exemple, une cible principale pourrait être le programme exécutable, tandis que d'autres cibles pourraient inclure la création de fichiers intermédiaires ou la documentation. Il est possible de lancer une cible spécifique avec par exemple `make doc` ou `make mon_prog`.

## Dépendances

Les dépendances décrivent les fichiers ou les cibles dont une cible donnée dépend. Si une dépendance est modifiée, la cible associée doit être reconstruite. Cela garantit que seuls les fichiers nécessaires sont recompilés.

## Règles

Les règles définissent comment construire une cible en spécifiant les commandes à exécuter. Ces commandes peuvent inclure des compilateurs, des éditeurs de liens, ou d'autres outils nécessaires à la construction du logiciel.

```
cible: dépendances
TABULATION  règles_de_construction
```



## Variables

Les variables permettent de définir des valeurs qui peuvent être utilisées à plusieurs endroits dans le Makefile. Cela facilite la maintenance et la mise à jour du fichier, car les valeurs peuvent être modifiées en un seul endroit.


## Un exemple
Voici un exemple simple de Makefile pour un programme C :

```
# Makefile
# les commentaires commenent par #

# deux variables : le compilateur et ses options
CC = g++
CFLAGS = -g -Wall
LIB = -lSDL2 -lSDL2_image

all: my_program

my_program: main.cpp functions.cpp
	$(CC) $(CFLAGS) -o my_program main.cpp functions.cpp $(LIB)

clean:
	rm -f my_program
```

Dans cet exemple, `my_program` est la cible principale, dépendant des fichiers source `main.c` et `functions.c`. La règle spécifie comment compiler ces fichiers pour créer l'exécutable. La cible `clean` est également définie pour supprimer l'exécutable généré.

Lorsque vous exécutez la commande `make` dans le répertoire contenant ce Makefile, il construira le programme en fonction des règles définies.
