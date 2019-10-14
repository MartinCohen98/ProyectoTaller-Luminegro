#ifndef PROYECTOTALLER_LUMINEGRO_SESION_H
#define PROYECTOTALLER_LUMINEGRO_SESION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using namespace std;

class Sesion {

private:
    SDL_Window* ventana;
    SDL_Renderer *renderizador;
    SDL_Texture *texturaTxtFijo1;
    SDL_Texture *texturaTxtFijo2;
    SDL_Texture *texturaTxtIngre;
    TTF_Font *fuente;
    string ingreso;

public:
    Sesion();
    bool buclear();
    virtual ~Sesion();
};


#endif //PROYECTOTALLER_LUMINEGRO_SESION_H
