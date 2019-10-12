#ifndef PROYECTOTALLER_LUMINEGRO_SESION_H
#define PROYECTOTALLER_LUMINEGRO_SESION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Sesion {

private:
    SDL_Window* ventana;

public:
    Sesion();
    virtual ~Sesion();
};


#endif //PROYECTOTALLER_LUMINEGRO_SESION_H
