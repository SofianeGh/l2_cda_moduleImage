#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Erreur SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        printf("Erreur IMG_Init: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "SDL3 - Affichage Image",
        800,
        600,
        SDL_WINDOW_RESIZABLE
    );

    if (!window)
    {
        printf("Erreur CreateWindow: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        printf("Erreur CreateRenderer: %s\n", SDL_GetError());
        return 1;
    }

    // Charger l’image (PNG par exemple)
    SDL_Surface *surface = IMG_Load("image.png");
    if (!surface)
    {
        printf("Erreur IMG_Load: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture)
    {
        printf("Erreur CreateTexture: %s\n", SDL_GetError());
        return 1;
    }

    int running = 1;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = 0;
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}