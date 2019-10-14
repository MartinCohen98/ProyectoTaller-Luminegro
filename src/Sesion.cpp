#include "Sesion.h"


int Sesion::clienteIniciarSesion() {

    Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ventana = SDL_CreateWindow("Luminegro Final Fight - Iniciar sesión",
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           640,
                                           480, 0);

    renderizador = SDL_CreateRenderer(ventana, -1, 0);

    fuente = TTF_OpenFont("assets/fonts/Ubuntu-M.ttf", 30);

    if (!fuente) {
        std::string mensajeError = "TTF_OpenFont: ";
        mensajeError.append( TTF_GetError() );
        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }

    SDL_Color colorTxtFijo = { 138, 212, 207 };
    SDL_Surface *superficieTxtFijo = TTF_RenderText_Solid(fuente, "Nombre de usuario:", colorTxtFijo);
    texturaTxtFijo1 = SDL_CreateTextureFromSurface(renderizador, superficieTxtFijo);

    superficieTxtFijo = TTF_RenderText_Solid(fuente, "Clave:", colorTxtFijo);
    texturaTxtFijo2 = SDL_CreateTextureFromSurface(renderizador, superficieTxtFijo);

    SDL_FreeSurface(superficieTxtFijo);

    while (buclearIngreUsuario()) {
        SDL_Delay(10);
    }

    return EXIT_SUCCESS;
}


bool Sesion::buclearIngreUsuario() {
    SDL_SetRenderDrawColor(renderizador, 44, 60, 74, 255 );
    SDL_RenderClear(renderizador);

    SDL_RenderCopy(renderizador, texturaTxtFijo1, NULL, &rectanguloTxtFijoSuperior);
    SDL_RenderCopy(renderizador, texturaTxtFijo2, NULL, &rectanguloTxtFijoInferior);

    while (SDL_PollEvent(&evento) != 0) {
        switch (evento.type) {
            case SDL_QUIT:
                return false;
            case SDL_TEXTINPUT:
                stringIngresado += evento.text.text;
                break;
            case SDL_KEYDOWN:
                if (evento.key.keysym.sym == SDLK_BACKSPACE && stringIngresado.size()) {
                    stringIngresado.pop_back();
                }
                break;
        }
    }

    atenderMostradoDeCursor();

    superficieTxtIngre = TTF_RenderText_Solid(fuente, stringIngresadoConCursor.c_str(),
                                                           colorTxtIngre);
    rectanguloTxtIngre.x = 320 - (superficieTxtIngre->w / 2.0f);
    rectanguloTxtIngre.w = superficieTxtIngre->w;

    texturaTxtIngre = SDL_CreateTextureFromSurface(renderizador, superficieTxtIngre);

    SDL_RenderCopy(renderizador, texturaTxtIngre, NULL, &rectanguloTxtIngre);
    SDL_DestroyTexture(texturaTxtIngre);
    SDL_FreeSurface(superficieTxtIngre);

    // Actualizar ventana
    SDL_RenderPresent(renderizador);

    return true;
}


void Sesion::atenderMostradoDeCursor() {
    stringIngresadoConCursor = stringIngresado;

    mostrarCursor = (i < 50);
    if (i == 100) {
        i = 0;
    } else {
        i++;
    }

    if (mostrarCursor) {
        stringIngresadoConCursor.append("|");
    } else {
        stringIngresadoConCursor.append(" ");
    }
}


void Sesion::limpiarMemoria() {
    TTF_CloseFont(fuente);
    TTF_Quit();
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(ventana);
    SDL_DestroyTexture(texturaTxtFijo1);
    SDL_DestroyTexture(texturaTxtFijo2);
    SDL_Quit();
}
