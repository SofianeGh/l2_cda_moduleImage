/**
@brief Module g�rant un Jeu (de Pacman)

@file Jeu.h
@date 2017/01/17
*/

#ifndef _JEU_H
#define _JEU_H

#include "Pacman.h"
#include "Terrain.h"
#include "Fantome.h"

/**
@brief Un jeu (de pacman) = un terrain et un pacman
*/
class Jeu
{

private:
    Terrain ter;
    Pacman pac;
    Fantome fan;

public:
    Jeu();

    const Terrain &getConstTerrain() const; //< \brief accesseur nécesseaire pour l'affichage
    const Pacman &getConstPacman() const;   //< \brief accesseur nécesseaire pour l'affichage
    const Fantome &getConstFantome() const; //< \brief accesseur nécesseaire pour l'affichage
    int getNombreDeFantome() const;         //< \brief accesseur nécesseaire pour l'affichage

    void actionsAutomatiques();
    bool actionClavier(const char touche); //< \brief rend vrai si mange une pastille, faux sinon
};

inline const Terrain &Jeu::getConstTerrain() const { return ter; } // du code court comme ca doit être en inline

inline const Pacman &Jeu::getConstPacman() const { return pac; }

inline const Fantome &Jeu::getConstFantome() const { return fan; }

inline int Jeu::getNombreDeFantome() const { return 1; }

#endif
