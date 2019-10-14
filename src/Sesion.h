#ifndef PROYECTOTALLER_LUMINEGRO_SESION_H
#define PROYECTOTALLER_LUMINEGRO_SESION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Logger.h"


class Sesion {

private:
    SDL_Window* ventana;
    SDL_Renderer *renderizador;
    SDL_Texture *texturaTxtFijo1;
    SDL_Texture *texturaTxtFijo2;
    SDL_Texture *texturaTxtIngre;
    TTF_Font *fuente;
    SDL_Event evento;
    SDL_Rect rectanguloTxtFijoSuperior = { 200, 40, 250, 37 };
    SDL_Rect rectanguloTxtFijoInferior = { 270, 200, 100, 37 };
    SDL_Rect rectanguloTxtIngre = { 0, 100, 250, 30 };
    SDL_Surface *superficieTxtIngre;
    SDL_Color colorTxtIngre = {100, 100, 100};
    std::string stringIngresado;
    std::string stringIngresadoConCursor;
    unsigned short int i = 0; // para conteos
    bool mostrarCursor = false; // Se muestra siempre, esta variable se usa en unos bucles
    bool buclearIngreUsuario();
    void atenderMostradoDeCursor(); // Se ocupa del cursor destellante que indica donde aparece lo que tecleás

public:
    int clienteIniciarSesion(); // Le ofrece al cliente ingresar sus credenciales para conectarse
    void limpiarMemoria();
};


#endif //PROYECTOTALLER_LUMINEGRO_SESION_H
