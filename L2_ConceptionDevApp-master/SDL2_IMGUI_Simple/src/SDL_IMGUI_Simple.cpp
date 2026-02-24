// g++ simple.cpp -lSDL2 -lSDL2_ttf -lSDL2_m_image

#include <cassert>
#include <time.h>
#include <stdlib.h>
// #include <SDL2/SDL.h>

#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
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
        string nfn = string("../") + filename;
        cout << "Error: cannot load " << filename << ". Trying " << nfn << endl;
        m_surface = IMG_Load(nfn.c_str());
        if (m_surface == nullptr)
        {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr)
    {
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
    SDL_GLContext m_gl_context; // IMGUI, il faut ceci en plus

    Image m_image;
    Image m_font_im;
    TTF_Font *m_font;

    void sdlAff();

    bool mb_drawImage;

public:
    SDLSimple();
    ~SDLSimple();
    void sdlBoucle();
};

SDLSimple::SDLSimple() : m_window(nullptr), m_renderer(nullptr), m_font(nullptr), mb_drawImage(true)
{
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
        cout << "SDL_m_image could not initialize! SDL_m_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int dimx, dimy;
    dimx = 640;
    dimy = 480;

    // ======== Creation de la fenetre avec  IMGUI ==================================================
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"); // IMGUI select driver
    const char *glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_window = SDL_CreateWindow("Demo IMGUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | window_flags); //| SDL_WINDOW_RESIZABLE);
    if (m_window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // SDL : Creation du renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    // IMGUI: les init
    m_gl_context = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, m_gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();
    ImGui_ImplSDL2_InitForOpenGL(m_window, m_gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // IMAGES
    m_image.loadFromFile("data/pacman.png", m_renderer);

    // FONTS + creation de l'image de titre "Pacman"
    string ttffile = string("data/DejaVuSansCondensed.ttf");
    int n = 0;
    do
    {
        m_font = TTF_OpenFont(ttffile.c_str(), 50);
        n++;
        ttffile = "../" + ttffile;
    } while (m_font == nullptr && n < 3);

    if (m_font == nullptr)
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
    // IMGUI: destroy
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(m_gl_context);

    // SDL destroy
    TTF_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDLSimple::sdlAff()
{
    // Afficher le sprite de Pacman
    float t = (cos(temps()) + 1.f) / 2.f;
    // cout<<t<<endl;
    if (!mb_drawImage)
        t = 1.f;

    m_image.draw(m_renderer, static_cast<int>(320 - 50 - 50 * t), static_cast<int>(200 - 50 - 50 * t),
                 static_cast<int>(100 + t * 100), static_cast<int>(100 + t * 100));

    // Affiche du texte
    m_font_im.draw(m_renderer, 320 - 50, 50, 100, 50);
}

void SDLSimple::sdlBoucle()
{
    SDL_Event event;
    bool quit = false;

    // tant que ce n'est pas la fin ...
    while (!quit)
    {

        // tant qu'il y a des evenements à traiter (cette boucle n'est pas bloquante)
        // SDL_PumpEvents();
        while (SDL_PollEvent(&event))
        {

            // IMGUI: manage event de IMGUI
            ImGui_ImplSDL2_ProcessEvent(&event);

            // SDL manage events
            if (event.type == SDL_QUIT)
                quit = true; // Si l'utilisateur a clique sur la croix de fermeture
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.scancode)
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

        // === IMGUI ===> Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window);

        // IMGUI : Le code de l'interface de IMGUI
        ImGui::NewFrame();
        ImGui::Begin("Display");
        ImGui::Text("Du texte..."); // Display some text (you can use a format strings too)
        ImGui::Checkbox("Image animée", &mb_drawImage);
        ImGui::End();
        ImGui::EndFrame();
        // IMGUI : Fin de l'interface

        // IMGUI : effacer l'écran
        glClearColor(0.2f, 0.1f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);

        // on affiche le jeu sur le buffer caché
        sdlAff();

        // IMGUI : afficher l'interface construite plus haut
        ImGui::Render();

        // glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        // glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle).
        // Avec IMGUI il ne faut plus faire RenderPresent, il faut permuter avec SDL_GL_SwapWindow
        // SDL_RenderPresent(m_renderer);
        SDL_GL_SwapWindow(m_window);
    }
}

int main(int, char **)
{
    SDLSimple sj;
    sj.sdlBoucle();
    return 0;
}