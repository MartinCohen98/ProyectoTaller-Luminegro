#include "Sesion.h"

Sesion::Sesion() {
    ventana = SDL_CreateWindow("Final Luminegro Fight",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               800, 600,
                               0);

    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();

    TTF_Font *fuente = TTF_OpenFont("assets/fonts/Ubuntu-M.ttf", 10);

    if (!fuente) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    TTF_Quit();
    TTF_CloseFont(fuente);
    SDL_DestroyWindow(ventana);
    SDL_Quit();
}


Sesion::~Sesion() {
    if (ventana) {
        SDL_DestroyWindow(ventana);
    }
    SDL_Quit();
}
