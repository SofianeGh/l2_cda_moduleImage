# Documentation de code avec Doxygen

Doxygen est un outil de documentation automatique très populaire utilisé principalement dans le domaine du développement logiciel, en particulier pour les langages de programmation comme le C, C++, C#, Java, et d'autres. Son objectif principal est de générer une documentation (HTML, PDF, etc.) à partir du code source d'un programme.


## En pratique

Voici comment générer la documentation de votre code au format HTML en supposant que votre projet SUPERPRJ est organisé de la manière suivante.

* superprj/src : les sources
* superprj/bin : les executables
* superprj/makefile ou superprj/CMakeList.txt

Depuis un terminal, entrez les commandes suivantes
```
    # Allez à la racine de votre projet
    cd superprj

    # Créez le fichier de configuration doxygen en tapant:
    doxygen -g doc/doxyfile

    # Personnalisez le fichier doxygen (au minimum INPUT et OUTPUT_DIRECTORY)
    code doc/doxyfile

    # Generez la documentation en tapant:
    doxygen doc/doxyfile

    # Une fois que Doxygen a terminé le processus de génération, il crée un répertoire de sortie (par défaut, html ou latex, selon la 
    # configuration) contenant la documentation générée. Ouvrez la page principale générée avec votre navigateur.
    firefox doc/html/index.html
```


## Les commentaires dans le code

Une fonction peut être commenté comme ceci
```
/**
 * @brief Description de la fonction.
 * 
 * @param param1 Description du premier paramètre.
 * @param param2 Description du deuxième paramètre.
 * @return Description de la valeur de retour.
 */
int maFonction(int param1, int param2);
```

Une donnée membre d'une classe et une classe
```
/**
 * @class MaClasse
 *
 * @brief Description détaillée de la classe MaClasse.
 *
 * Une classe pour illustrer l'utilisation de Doxygen pour générer de la documentation.
 */
class MaClasse {
public:
    int donneeMembre; ///< Description de la donneeMembre.
};
```





## Pour aller plus loin
* [Manuel d'utilisation de doxygen](https://www.doxygen.nl/)
* doxygen peut aussi générer un diagramme des classes (si Dot est installé)
