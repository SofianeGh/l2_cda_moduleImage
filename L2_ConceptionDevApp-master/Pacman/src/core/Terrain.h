/**
@brief Module gérant un terrain dans l'application Pacman

Un terrain dans l'application Pacman est un tableau 2D de caractères dont la taille est dimx x dimy.
Un terrain ne peut pas dépasser 100x100 cases (ATTENTION : il n'y pas de vérification de ceci).

@file Terrain.h
@date 2017/01/17
*/

#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <cassert>

/**
@brief La classe Terrain contient ses dimensions et un tab 2D de cases (une case=1 char)
*/
class Terrain
{

private:
    enum TypeCase
    {
        SPACE = ' ',
        WALL = '#',
        DOT = '.'
    }; // Les enum sont d'habitude initialisé avec des nombres, ici on a une équivalence caractère/nombre

    int m_dimx;
    int m_dimy;
    // char m_ter [100][100];
    TypeCase m_ter[100][100];

public:
    /**
    @brief <B>Construit</B> un objet Terrain.
    Le constructeur remplit dimx et dimy et les cases du tableau ter avec un terrain par défaut.
    @bug S'il y a un bug dans le constructeur, je peux le signaler ici ...
    */
    Terrain();

    /**
    @brief Renvoie vrai si on peut positionnner un personnage aux coordonnées (x,y), faux sinon
    @param x : abs de la case à tester
    @param y : ordonnée de la case à tester
    */
    bool estPositionPersoValide(const int x, const int y) const;

    /**
    @brief Mange une pastille en case (x,y)
    @param x : abs de la case de la pastille
    @param y : ordonnée de la case de la pastille
    */
    void mangePastille(const int x, const int y);

    /**
    @brief Renvoie le type d'objet se trouvant en (x,y)
    @param x : abs de la case de l'objet
    @param y : ordonnée de la case de l'objet
    */
    TypeCase getXY(const int x, const int y) const;

    /**
    @brief Renvoie le type d'objet se trouvant en (x,y)
    @param x : abs de la case de l'objet
    @param y : ordonnée de la case de l'objet
    */
    unsigned char getXYasChar(const int x, const int y) const;

    /**
    @brief Renvoie la largeur du terrain
    */
    int getDimX() const;

    /**
    @brief Renvoie la hauteur du terrain
    */
    int getDimY() const;
};

inline int Terrain::getDimX() const { return m_dimx; }

inline int Terrain::getDimY() const { return m_dimy; }

inline Terrain::TypeCase Terrain::getXY(const int x, const int y) const
{
    assert(x >= 0);
    assert(y >= 0);
    assert(x < m_dimx);
    assert(y < m_dimy);
    return m_ter[x][y];
}

inline unsigned char Terrain::getXYasChar(const int x, const int y) const
{
    assert(x >= 0);
    assert(y >= 0);
    assert(x < m_dimx);
    assert(y < m_dimy);
    return (char)(m_ter[x][y]); // ceci ne marche que dans notre cas particulier, car l'enum est initialisé avec les codes ascii
}

#endif
