/**
@brief Module gérant un fantome
@file Fantome.h
@date 2017/01/17
*/

#ifndef _FANTOME_H
#define _FANTOME_H

#include "Terrain.h"
#include "Pacman.h"

/**
@brief Un fantome = sa position 2D
*/
class Fantome
{

private:
    int m_x;
    int m_y;
    int m_dir;

public:
    Fantome();

    void gauche(const Terrain &t);
    void droite(const Terrain &t);
    void haut(const Terrain &t);
    void bas(const Terrain &t);

    int getX() const;
    int getY() const;

    void versPacman(const Terrain &t, const Pacman &p); //< \brief bouge en direction du Pacman, quand Pacman vurlnérable
    void bougeAuto(const Terrain &t);                   //< \brief bouge en aller/retour
};

inline void Fantome::gauche(const Terrain &t)
{
    if (t.estPositionPersoValide(m_x - 1, m_y))
        m_x--;
}

inline void Fantome::droite(const Terrain &t)
{
    if (t.estPositionPersoValide(m_x + 1, m_y))
        m_x++;
}

inline void Fantome::haut(const Terrain &t)
{
    if (t.estPositionPersoValide(m_x, m_y + 1))
        m_y++;
}

inline void Fantome::bas(const Terrain &t)
{
    if (t.estPositionPersoValide(m_x, m_y - 1))
        m_y--;
}

inline int Fantome::getX() const { return m_x; }

inline int Fantome::getY() const { return m_y; }

#endif
