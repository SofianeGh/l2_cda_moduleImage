
# ImGUI

"Dear ImGui" (ou "ImGui") est une bibliothèque d'interface utilisateur (UI) pour le C++. "Dear ImGui" signifie "Immediate Mode GUI". Elle se distingue par son approche "Immediate Mode" par opposition au mode "Retained Mode" plus traditionnel. Cela signifie que l'interface utilisateur est entièrement recréée à chaque frame, simplifiant la conception et la mise à jour.

* Légèreté : ImGui est conçu pour être léger et facile à intégrer dans des projets C++.
* Sans dépendances externes : Il n'a pas de dépendances autres que les bibliothèques standard C++.
* Simplicité d'utilisation : La syntaxe est simple et intuitive, ce qui facilite la création d'interfaces utilisateur interactives.
* Personnalisable : Vous pouvez personnaliser les thèmes et les styles selon vos besoins.

Regardez l'exemple dans le [répertoire SDL2_IMGUI_Simple](../SDL2_IMGUI_Simple/).



```
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

int main(int, char**) {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        return -1;
    }

    // Configurer SDL pour OpenGL 3.2 avec un profil de base
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Créer une fenêtre avec OpenGL
    SDL_Window* window = SDL_CreateWindow("ImGui SDL2+OpenGL3 Example", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    // Créer un contexte OpenGL
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    // Charger les extensions OpenGL avec ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Configurer les backends pour SDL et OpenGL
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");

    // Boucle principale
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Début du cadre ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        // Créez ici votre interface utilisateur ImGui

        // Fin du cadre ImGui
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Nettoyage
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```