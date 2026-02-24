// g++ simple.cpp -lSDL2 -lSDL2_ttf -lSDL2_m_image

#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <filesystem>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
using namespace std;

const int TAILLE_SPRITE = 32;

float temps()
{
    return float(SDL_GetTicks()) * 1000.f / CLOCKS_PER_SEC; // conversion des ms en secondes en divisant par 1000
}

// ============= CLASS IMAGE =============== //
//! \brief Pour gérer une m_image avec SDL2
class Image
{

private:
    SDL_Surface *m_surface;
    SDL_Texture *m_texture;
    bool m_hasChanged;

public:
    Image();
    ~Image();
    void loadFromFile(const char *filename, SDL_Renderer *m_renderer);
    void loadFromCurrentSurface(SDL_Renderer *m_renderer);
    void draw(SDL_Renderer *m_renderer, int x, int y, int w = -1, int h = -1);
    SDL_Texture *getTexture() const;
    void setSurface(SDL_Surface *surf);
};

Image::Image() : m_surface(nullptr), m_texture(nullptr), m_hasChanged(false)
{
}

Image::~Image()
{
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}

void Image::loadFromFile(const char *filename, SDL_Renderer *m_renderer)
{
    m_surface = IMG_Load(filename);
    if (m_surface == nullptr)
    {
        string nfn = string(filename);
        int n = 0;
        while ((m_surface == nullptr) && (n < 3))
        {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr)
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::cout << "Répertoire courant : " << currentPath << std::endl;
        cout << "Error: cannot load " << filename << endl;
        exit(1);
    }

    SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(m_surface);
    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(m_renderer, surfaceCorrectPixelFormat);
    if (m_texture == nullptr)
    {
        cout << "Error: problem to create the texture of " << filename << endl;
        exit(1);
    }
}

void Image::loadFromCurrentSurface(SDL_Renderer *m_renderer)
{
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    if (m_texture == nullptr)
    {
        cout << "Error: problem to create the texture from surface " << endl;
        exit(1);
    }
}

void Image::draw(SDL_Renderer *m_renderer, int x, int y, int w, int h)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w < 0) ? m_surface->w : w;
    r.h = (h < 0) ? m_surface->h : h;

    if (m_hasChanged)
    {
        ok = SDL_UpdateTexture(m_texture, nullptr, m_surface->pixels, m_surface->pitch);
        assert(ok == 0);
        m_hasChanged = false;
    }

    ok = SDL_RenderCopy(m_renderer, m_texture, nullptr, &r);
    assert(ok == 0);
}

SDL_Texture *Image::getTexture() const { return m_texture; }

void Image::setSurface(SDL_Surface *surf) { m_surface = surf; }

// ============= CLASS SDLJEU =============== //

/**
    La classe gerant le jeu avec un affichage SDL
*/
class SDLSimple
{

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

    Image m_image;
    Image m_font_im;
    TTF_Font *m_font;

    void sdlAff();

    bool withSound;

public:
    SDLSimple();
    ~SDLSimple();
    void sdlBoucle();
};

SDLSimple::SDLSimple() : m_window(nullptr), m_renderer(nullptr), m_font(nullptr)
{
    // Initialisation de la SDL
    cout << "SDL: init" << endl;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    cout << "SDL_ttf: init" << endl;
    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    cout << "SDL_image: init" << endl;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_m_image could not initialize! SDL_m_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int dimx, dimy;
    dimx = 640;
    dimy = 480;

    // Creation de la fenetre
    m_window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (m_window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    // IMAGES
    m_image.loadFromFile("data/pacman.png", m_renderer);

    // FONTS
    string ttffile = string("data/DejaVuSansCondensed.ttf");
    int n = 0;
    do
    {
        m_font = TTF_OpenFont(ttffile.c_str(), 50);
        ttffile = "../" + ttffile;
    } while ((m_font == NULL) && (n < 3));
    if (m_font == NULL)
    {
        cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Color m_font_color;
    m_font_color.r = 50;
    m_font_color.g = 50;
    m_font_color.b = 255;
    m_font_im.setSurface(TTF_RenderText_Solid(m_font, "Pacman", m_font_color));
    m_font_im.loadFromCurrentSurface(m_renderer);
}

SDLSimple::~SDLSimple()
{
    TTF_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDLSimple::sdlAff()
{
    // Remplir l'écran de blanc
    SDL_SetRenderDrawColor(m_renderer, 130, 140, 255, 255);
    SDL_RenderClear(m_renderer);

    // Afficher le sprite de Pacman
    float t = (cos(0.01f * temps()) + 1.f) / 2.f;
    // cout<<t<<endl;
    m_image.draw(m_renderer, static_cast<int>(320 - 50 - 50 * t), static_cast<int>(200 - 50 - 50 * t),
                 static_cast<int>(100 + t * 100), static_cast<int>(100 + t * 100));

    // Affiche du texte
    m_font_im.draw(m_renderer, 320 - 50, 50, 100, 50);
}

void SDLSimple::sdlBoucle()
{
    SDL_Event events;
    bool quit = false;

    // tant que ce n'est pas la fin ...
    while (!quit)
    {

        // tant qu'il y a des evenements à traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true; // Si l'utilisateur a clique sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN)
            {
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                case SDL_SCANCODE_Q:
                    quit = true;
                    break;
                default:
                    break;
                }
            }
        }

        // on affiche le jeu sur le buffer caché
        sdlAff();

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(m_renderer);
    }
}

int main(int, char **)
{
    SDLSimple sj;
    sj.sdlBoucle();
    return 0;
}