#ifndef _SDLJEU_H
#define _SDLJEU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Jeu.h"

#include "SDLSprite.h"

/**
    La classe gerant le jeu avec un affichage SDL
*/
class SDLJeu
{

private:
    Jeu jeu;

    SDL_Window *window;
    SDL_Renderer *renderer;

    TTF_Font *font;
    SDLSprite font_im;
    SDL_Color font_color;

    Mix_Chunk *sound;
    bool withSound;

    SDLSprite im_pacman;
    SDLSprite im_mur;
    SDLSprite im_pastille;
    SDLSprite im_fantome;

    bool souris;
    bool touche;

public:
    SDLJeu();
    ~SDLJeu();
    void sdlBoucle();
    void sdlAff();
};

#endif
