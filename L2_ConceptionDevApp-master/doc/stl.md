STL, ou Standard Template Library, est une puissante collection de classes modèles en C++. Elle propose des classes et des fonctions génériques qui implémentent de nombreux algorithmes et structures de données populaires et couramment utilisés, tels que les vecteurs, les listes, les files d'attente et les piles. L'objectif de la STL est de fournir une base solide et efficace pour la programmation en C++, en favorisant la réutilisation du code, la maintenabilité et l'efficacité.

Les composants clés de la STL comprennent :

1. **Conteneurs**. Ce sont des classes qui stockent des éléments de données. Les exemples incluent les vecteurs (tableaux dynamiques), les listes (listes chaînées), les files d'attente, les piles, et plus encore. Les conteneurs offrent un moyen de stocker et d'organiser des données de manière flexible.

2. **Algorithmes**. La STL propose un ensemble d'algorithmes génériques qui peuvent être utilisés avec différents types de conteneurs : tri, rrecherche etc.

3. **Itérateurs**. Les itérateurs sont utilisés pour parcourir les éléments d'un conteneur de manière générique, indépendamment du type spécifique de conteneur.



## Un exemple simple

```
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Création d'un vecteur de nombres
    std::vector<int> nombres = {5, 2, 8, 1, 7};

    // Affichage du vecteur non trié
    std::cout << "Vecteur non trié : ";
    for (int nombre : nombres) {
        std::cout << nombre << " ";
    }
    std::cout << std::endl;

    // Tri du vecteur en utilisant la fonction sort de la STL
    std::sort(nombres.begin(), nombres.end());

    // Affichage du vecteur trié
    std::cout << "Vecteur trié : ";
    for (int nombre : nombres) {
        std::cout << nombre << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

## Documentations

* [CPP reference](https://en.cppreference.com/w/cpp/container)
* [CPP STL](https://cplusplus.com/reference/stl/)
