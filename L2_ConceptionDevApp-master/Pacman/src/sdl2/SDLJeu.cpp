#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "SDLJeu.h"

using namespace std;

const int TAILLE_SPRITE = 32;

float temps()
{
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC; // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS SDLJEU =============== //

SDLJeu::SDLJeu() : jeu()
{
    cout<<"SDL init ..."<<endl;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        // SDL_Quit();exit(1);
        withSound = false;
    }
    else
        withSound = true;

    cout<<"SDL init done"<<endl;

    int dimx, dimy;
    dimx = jeu.getConstTerrain().getDimX();
    dimy = jeu.getConstTerrain().getDimY();
    dimx = dimx * TAILLE_SPRITE;
    dimy = dimy * TAILLE_SPRITE;

    // Creation de la fenetre
    window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_pacman.loadFromFile("data/pacman.png", renderer);
    im_mur.loadFromFile("data/mur.png", renderer);
    im_pastille.loadFromFile("data/pastille.png", renderer);
    im_fantome.loadFromFile("data/fantome.png", renderer);

    // FONTS
    font = TTF_OpenFont("data/DejaVuSansCondensed.ttf", 50);
    if (font == nullptr)
        font = TTF_OpenFont("../data/DejaVuSansCondensed.ttf", 50);
    if (font == nullptr)
    {
        cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    font_color.r = 50;
    font_color.g = 50;
    font_color.b = 255;
    font_im.setSurface(TTF_RenderText_Solid(font, "Pacman", font_color));
    font_im.loadFromCurrentSurface(renderer);

    // SONS
    if (withSound)
    {
        sound = Mix_LoadWAV("data/son.wav");
        if (sound == nullptr)
            sound = Mix_LoadWAV("../data/son.wav");
        if (sound == nullptr)
        {
            cout << "Failed to load son.wav! SDL_mixer Error: " << Mix_GetError() << endl;
            SDL_Quit();
            exit(1);
        }
    }
    cout<<"Jeu::Jeu(): done"<<endl;
}

SDLJeu::~SDLJeu()
{
    if (withSound)
        Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLJeu::sdlAff()
{
    // Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    int x, y;
    const Terrain &ter = jeu.getConstTerrain();
    const Pacman &pac = jeu.getConstPacman();
    const Fantome &fan = jeu.getConstFantome();

    // Afficher les sprites des murs et des pastilles
    for (x = 0; x < ter.getDimX(); ++x)
        for (y = 0; y < ter.getDimY(); ++y)
            if (ter.getXY(x, y) == '#')
                im_mur.draw(renderer, x * TAILLE_SPRITE, y * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);
            else if (ter.getXY(x, y) == '.')
                im_pastille.draw(renderer, x * TAILLE_SPRITE, y * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);

    // Afficher le sprite de Pacman
    im_pacman.draw(renderer, pac.getX() * TAILLE_SPRITE, pac.getY() * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);

    // Afficher le sprite du Fantome
    im_fantome.draw(renderer, fan.getX() * TAILLE_SPRITE, fan.getY() * TAILLE_SPRITE, TAILLE_SPRITE, TAILLE_SPRITE);

    // Ecrire un titre par dessus
    SDL_Rect positionTitre;
    positionTitre.x = 270;
    positionTitre.y = 49;
    positionTitre.w = 100;
    positionTitre.h = 30;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTitre);
}

void SDLJeu::sdlBoucle()
{
    SDL_Event events;
    bool quit = false;

    Uint32 t = SDL_GetTicks(), nt;

    // tant que ce n'est pas la fin ...
    while (!quit)
    {

        nt = SDL_GetTicks();
        if (nt - t > 500)
        {
            jeu.actionsAutomatiques();
            t = nt;
        }

        // tant qu'il y a des évenements à traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true; // Si l'utilisateur a clique sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN)
            { // Si une touche est enfoncee
                bool mangePastille = false;
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_UP:
                    mangePastille = jeu.actionClavier('b'); // car Y inverse
                    break;
                case SDL_SCANCODE_DOWN:
                    mangePastille = jeu.actionClavier('h'); // car Y inverse
                    break;
                case SDL_SCANCODE_LEFT:
                    mangePastille = jeu.actionClavier('g');
                    break;
                case SDL_SCANCODE_RIGHT:
                    mangePastille = jeu.actionClavier('d');
                    break;
                case SDL_SCANCODE_ESCAPE:
                case SDL_SCANCODE_Q:
                    quit = true;
                    break;
                default:
                    break;
                }
                if ((withSound) && (mangePastille))
                    Mix_PlayChannel(-1, sound, 0);
            }
        }

        sdlAff();

        SDL_RenderPresent(renderer);
    }
}
