#include "Sesion.h"

Sesion::Sesion() {

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *ventana = SDL_CreateWindow("Luminegro Final Fight - Iniciar sesión",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640,
                                          480, 0);

    renderizador = SDL_CreateRenderer(ventana, -1, 0);

    fuente = TTF_OpenFont("assets/fonts/Ubuntu-M.ttf", 30);

    if (!fuente) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    SDL_Color color = { 138, 212, 207 };
    SDL_Surface *superficieTxtFijo = TTF_RenderText_Solid(fuente,
            "Nombre de usuario:", color);
    texturaTxtFijo1 = SDL_CreateTextureFromSurface(renderizador, superficieTxtFijo);

    superficieTxtFijo = TTF_RenderText_Solid(fuente, "Clave:", color);
    texturaTxtFijo2 = SDL_CreateTextureFromSurface(renderizador, superficieTxtFijo);

    while (buclear()) {
        SDL_Delay(10);
    }

    TTF_CloseFont(fuente);
    TTF_Quit();
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(ventana);
    SDL_DestroyTexture(texturaTxtFijo1);
    SDL_DestroyTexture(texturaTxtFijo2);
    SDL_FreeSurface(superficieTxtFijo);
    SDL_Quit();
}


bool Sesion::buclear() {
    SDL_Event evento;
    SDL_Rect rectanguloTxtFijo;
    SDL_Rect rectanguloTxtIngre = { 0, 100, 250, 30 };

    SDL_SetRenderDrawColor(renderizador, 44, 60, 74, 255 );
    SDL_RenderClear(renderizador);

    rectanguloTxtFijo = { 200, 40, 250, 40 };
    SDL_RenderCopy(renderizador, texturaTxtFijo1, NULL, &rectanguloTxtFijo);

    rectanguloTxtFijo = { 270, 190, 100, 40 };
    SDL_RenderCopy(renderizador, texturaTxtFijo2, NULL, &rectanguloTxtFijo);

    // Event loop
    while (SDL_PollEvent(&evento) != 0) {
        switch (evento.type) {
            case SDL_QUIT:
                return false;
            case SDL_TEXTINPUT:
                ingreso += evento.text.text;
                break;
            case SDL_KEYDOWN:
                if (evento.key.keysym.sym == SDLK_BACKSPACE && ingreso.size()) {
                    ingreso.pop_back();
                }
                break;
        }
    }

    SDL_Color colorTxtIngre = {100, 100, 100};

    if (ingreso.size()) {
        SDL_Surface* superficieTxtIngre = TTF_RenderText_Solid(fuente, ingreso.c_str(),
                colorTxtIngre);
        texturaTxtIngre = SDL_CreateTextureFromSurface(renderizador, superficieTxtIngre);

        rectanguloTxtIngre.x = 320 - (superficieTxtIngre->w / 2.0f);
        rectanguloTxtIngre.w = superficieTxtIngre->w;

        SDL_RenderCopy(renderizador, texturaTxtIngre, NULL, &rectanguloTxtIngre);
        SDL_DestroyTexture(texturaTxtIngre);
        SDL_FreeSurface(superficieTxtIngre);
    }

    // Update window
    SDL_RenderPresent(renderizador);

    return true;
}


Sesion::~Sesion() {
    if (ventana) {
        SDL_DestroyWindow(ventana);
    }
    SDL_Quit();
}
